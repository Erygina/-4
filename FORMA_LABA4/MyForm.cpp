#include "MyForm.h"
#include<iostream>
#include <random>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^ >^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FORMALABA4::MyForm form;
	Application::Run(% form);
}

using namespace std; 
ifstream test;

int numLayers = 4, lSz[4] = { 3,3,3,1 };
double beta = 0.8, alpha = 1, eps = 0.0001;
long num_iter = 5000;
//0, 0, 0, 0,
//1, 1, 1, 1,
//0.2, 0.3, 0.4, 0.024,
//0.5, 0.5, 0.5, 0.125,
//1, 0.8, 1, 0.8,
//0, 0.5, 0.7, 0,
//0.9, 0.2, 0.1, 0.018,
//0.6, 0.4, 0.3, 0.072
// 
// 
//0, 0, 0, 0,
//1, 1, 1, 1,
//0.4 0.5 0.9 0.18
//1 0.7 0.7 0.49
//1 0.8 0.3 0.24
//0.2 0.5 1 0.1
//0.4 0.8 1 0.32
//0.5 0.8 0.1 0.04
// 
// 
//0, 0, 0, 0,
//1, 1, 1, 1,
//0.4 0.5 1 0.2
//1 0.5 0.6 0.3
//1 0.8 0.3 0.24
//0.2 0.5 1 0.1
//0.4 0.8 1 0.32
//0.5 0.8 0.1 0.04
// 

class net {
    // выход каждого нейрона
    double** out;
    // значение дельта-ошибки для каждого нейрона
    double** delta;
    // 3-D массив для хранения весов для каждого нейрона
    double*** weight;

    // хранение для изменения веса, сделанного в предыдущей эпохе
    double*** before_weight;

    double** offset;  //  массив смещений
    double** before_offset;  //  массив для изменения смещений


public:

    ~net();

    // ввод весов с файла
    void fix_weight() {
        ifstream off, w;
        off.open("offset.txt");
        w.open("weight.txt");

        for (int i = 1; i < numLayers; i++) {
            for (int j = 0; j < lSz[i]; j++) {
                for (int k = 0; k < lSz[i - 1]; k++) {
                    w >> weight[i][j][k];
                }
                w >> weight[i][j][lSz[i - 1]];
            }
        }

        for (int i = 0; i < numLayers; i++)
        {
            for (int j = 0; j < lSz[i]; j++)
                off >> offset[i][j];
        }

    }

    // инициализирует и выделяет память
    net(int nl, int* sz, double b, double a);

    // ошибка обратного распространения для одного набора входных
    void error(double* in, double* tgt);

    // вычисление значений нейронов
    void forward(double* in);

    // возвращает среднеквадратичную ошибку 
    double E_w(double* tgt)
    {
        double mse = 0;
        for (int i = 0; i < lSz[numLayers - 1]; i++) {
            mse += 0.5 * (tgt[i] - out[numLayers - 1][i]) * (tgt[i] - out[numLayers - 1][i]);
        }
        //cout<<"o "<< mse / lSz[numLayers - 1]<<endl ;
        return(double)(mse / lSz[numLayers - 1]);
    }

    // возвращает i-й вывод 
    double Out()
    {
        //for (int j = 0; j < lsize[i]; j++)
        return out[numLayers - 1][0];
    }

    // сигмоидная функция
    double sigmoid(double  SUM, int i, int j)
    {
        return (double)(1 / (1 + exp(-alpha * (SUM + offset[i][j]))));
        //return -alpha * SUM;
        //return 0;
    }

    void infile()
    {
        ofstream off, w;
        off.open("offset.txt");
        w.open("weight.txt");

        for (int i = 1; i < numLayers; i++) {
            for (int j = 0; j < lSz[i]; j++) {
                for (int k = 0; k < lSz[i - 1]; k++) {
                    w << weight[i][j][k] << "  " << endl;
                }
                w << weight[i][j][lSz[i - 1]] << "  " << endl;
            }
        }

        for (int i = 0; i < numLayers; i++)
        {
            for (int j = 0; j < lSz[i]; j++)
                off << offset[i][j] << " ";
            off << endl;
        }

    }
};


net::net(int nl, int* sz, double b, double a)
{
    // установить количество слоев и их размеры
    int numl = nl, i;
    /*lsize = new int[numl];

    for (int i = 0; i < numl; i++) {
        lsize[i] = sz[i];
    }*/

    // выделение памяти для вывода каждого нейрона
    out = new double* [numl];

    for (i = 0; i < numl; i++) {
        out[i] = new double[lSz[i]];
    }

    //СМЕЩЕНИЕ
    offset = new double* [numl];
    for (i = 0; i < numl; i++)
    {
        offset[i] = new double[lSz[i]];
        for (int j = 0; j < lSz[i]; j++)
        {
            if (i == 0)  offset[i][j] = 0; // для входного нет смещения
            else offset[i][j] = (double)(rand()) / (RAND_MAX / 2) - 1;
        }
    }

    //для изменения смещений
    before_offset = new double* [numl];
    for (i = 0; i < numl; i++)
    {
        before_offset[i] = new double[lSz[i]];
        for (int j = 0; j < lSz[i]; j++)
        {
            before_offset[i][j] = 0;
        }
    }

    // выделение памяти для дельты
    delta = new double* [numl];

    for (i = 1; i < numl; i++) {
        delta[i] = new double[lSz[i]];
    }

    // выделение памяти для весов
    weight = new double** [numl];

    for (i = 1; i < numl; i++) {
        weight[i] = new double* [lSz[i]];
    }
    for (i = 1; i < numl; i++) {
        for (int j = 0; j < lSz[i]; j++) {
            weight[i][j] = new double[lSz[i - 1] + 1];
        }
    }


    // выделение памяти для предыдущих весов
    before_weight = new double** [numl];

    for (i = 1; i < numl; i++) {
        before_weight[i] = new double* [lSz[i]];

    }
    for (i = 1; i < numl; i++) {
        for (int j = 0; j < lSz[i]; j++) {
            before_weight[i][j] = new double[lSz[i - 1] + 1];
        }
    }

    // назначение случайных весов
    srand((unsigned)(time(NULL)));
    for (i = 1; i < numl; i++)
        for (int j = 0; j < lSz[i]; j++)
            for (int k = 0; k < lSz[i - 1] + 1; k++)
                weight[i][j][k] = (double)(rand()) / (RAND_MAX / 2) - 1;


    // инициализировать предыдущие веса 0 для первой итерации
    for (i = 1; i < numl; i++)
        for (int j = 0; j < lSz[i]; j++)
            for (int k = 0; k < lSz[i - 1] + 1; k++)
                before_weight[i][j][k] = (double)0.0;

}

void net::forward(double* in)
{
    int i, j;
    double sum;
    for (i = 0; i < lSz[0]; i++)
        out[0][i] = in[i];
    // назначить выходное  значение каждому нейрону 
            // Для каждого слоя
    for (i = 1; i < numLayers; i++) {
        for (j = 0; j < lSz[i]; j++) {
            sum = 0.0;
            for (int k = 0; k < lSz[i - 1]; k++) {
                // Умножить вес  на значение нейрона предыдущего слоя и добавить к сумме
                sum += out[i - 1][k] * weight[i][j][k]; //Сумматор
            }
            // Прибавить смещение
            sum += weight[i][j][lSz[i - 1]];
            // Применить сигмоидальную функцию
            out[i][j] = sigmoid(sum, i, j);
        }
    }
}

void net::error(double* in, double* tgt)    //Ошибка обратного распространения
{
    double sum;
    forward(in);

    //=======Найти дельту для выходного слоя=======
    for (int i = 0; i < lSz[numLayers - 1]; i++) {
        delta[numLayers - 1][i] = out[numLayers - 1][i] *
            (1 - out[numLayers - 1][i]) * (tgt[i] - out[numLayers - 1][i]);
    }

    //=====Найти дельту для скрытых слоев======
    for (int i = numLayers - 2; i > 0; i--)
    {
        for (int j = 0; j < lSz[i]; j++)
        {
            sum = 0.0;
            for (int k = 0; k < lSz[i + 1]; k++)
            {
                //cout << "1";
                sum += delta[i + 1][k] * weight[i + 1][k][j];
            }
            delta[i][j] = out[i][j] * (1 - out[i][j]) * sum;
        }
    }


    for (int i = 1; i < numLayers; i++) {
        for (int j = 0; j < lSz[i]; j++) {
            for (int k = 0; k < lSz[i - 1]; k++) {
                weight[i][j][k] += alpha * before_weight[i][j][k];

            }
            weight[i][j][lSz[i - 1]] += alpha * before_weight[i][j][lSz[i - 1]];
        }
    }

    //=======корректировка весов========
    for (int i = 1; i < numLayers; i++) {
        for (int j = 0; j < lSz[i]; j++) {

            for (int k = 0; k < lSz[i - 1]; k++)
            {
                before_weight[i][j][k] = beta * delta[i][j] * out[i - 1][k];
                weight[i][j][k] += before_weight[i][j][k];
            }
            before_weight[i][j][lSz[i - 1]] = beta * delta[i][j];
            weight[i][j][lSz[i - 1]] += before_weight[i][j][lSz[i - 1]];
        }
    }

    //======Корректировка смещений=========
    for (int i = 1; i < numLayers - 1; i++)
    {
        for (int j = 0; j < lSz[i]; j++)
        {
            before_offset[i][j] = beta * delta[i][j] * 1;
            offset[i][j] += before_offset[i][j];
        }
    }

}

net* bp = new net(numLayers, lSz, beta, alpha);
System::Void FORMALABA4::MyForm::studyButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    srand(time(0));
        test.open("test.txt");    
            double data[500][4];
            for (int k = 0; k < 500; k++)
            {
                for (int u = 0; u < 4; u++)
                {
                    test >> data[k][u];
                }
            }
           
            double Ew;
            int ep;
    
    
            //=======Обучение=======
            for (ep = 0; ep < num_iter; ep++)
            {
                Ew = 0.0;
                for (int i = 0; i < 500; i++)
                {
                    bp->error(data[i], &data[i][lSz[0]]);
                    Ew += bp->E_w(&data[i][lSz[0]]);
                }
                Ew /= 500;
                if (Ew < eps)
                    break;
    
            }
            //cout << endl;
            //cout << "Network trained in " << ep << " epochs. MSE: " << Ew << endl;
            //bp->infile();

    
        
    return System::Void();
}

System::Void FORMALABA4::MyForm::multiplyButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    double testData[3];
    bp->fix_weight();
    testData[0] = Convert::ToDouble(textBox1->Text);
    testData[1] = Convert::ToDouble(textBox2->Text);
    testData[2] = Convert::ToDouble(textBox3->Text);
    
        //========Тесты========    
     bp->forward(testData);
     double result = int(100 * bp->Out() + 0.5) / 100.0;
     resultTextBox->Text = "Результат: ";
     resultTextBox->Text += Convert::ToString(result);
    return System::Void();
}





