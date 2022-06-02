#pragma once

namespace FORMALABA4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ resultTextBox;
	private: System::Windows::Forms::Button^ studyButton;
	private: System::Windows::Forms::Button^ multiplyButton;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->resultTextBox = (gcnew System::Windows::Forms::TextBox());
			this->studyButton = (gcnew System::Windows::Forms::Button());
			this->multiplyButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(2, -1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1006, 595);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(678, 91);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(81, 20);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(775, 91);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(81, 20);
			this->textBox2->TabIndex = 2;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(872, 91);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(81, 20);
			this->textBox3->TabIndex = 3;
			// 
			// resultTextBox
			// 
			this->resultTextBox->Location = System::Drawing::Point(678, 139);
			this->resultTextBox->Name = L"resultTextBox";
			this->resultTextBox->Size = System::Drawing::Size(275, 20);
			this->resultTextBox->TabIndex = 4;
			// 
			// studyButton
			// 
			this->studyButton->Location = System::Drawing::Point(678, 181);
			this->studyButton->Name = L"studyButton";
			this->studyButton->Size = System::Drawing::Size(81, 23);
			this->studyButton->TabIndex = 5;
			this->studyButton->Text = L"Обучить";
			this->studyButton->UseVisualStyleBackColor = true;
			
			// 
			// multiplyButton
			// 
			this->multiplyButton->Location = System::Drawing::Point(775, 180);
			this->multiplyButton->Name = L"multiplyButton";
			this->multiplyButton->Size = System::Drawing::Size(81, 23);
			this->multiplyButton->TabIndex = 6;
			this->multiplyButton->Text = L"Умножить";
			this->multiplyButton->UseVisualStyleBackColor = true;
			this->multiplyButton->Click += gcnew System::EventHandler(this, &MyForm::multiplyButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1007, 594);
			this->Controls->Add(this->multiplyButton);
			this->Controls->Add(this->studyButton);
			this->Controls->Add(this->resultTextBox);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void studyButton_Click(System::Object^ sender, System::EventArgs^ e);
	
private: System::Void multiplyButton_Click(System::Object^ sender, System::EventArgs^ e);

};
}
