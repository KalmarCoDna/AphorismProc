#include "pch.h"
#include "CppUnitTest.h"

#include "../AphorismProc/Header.h"
#include "../AphorismProc/Source.cpp"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(In_Aphorism_Test)
		{
			Aphorism* A_exp = new Aphorism;

			A_exp->Author = "Benjamin Disraeli";

			ifstream ifst("../AphorismProc/in_aphorism.txt");

			Aphorism* A_act = new Aphorism;

			A_act = (Aphorism*)In_Aphorism(ifst);

			Assert::AreEqual(A_exp->Author, A_act->Author);
		}
		TEST_METHOD(In_Proverb_Test)
		{
			Proverb* P_exp = new Proverb;

			P_exp->Country = "England";

			ifstream ifst("../AphorismProc/in_proverb.txt");

			Proverb* P_act = new Proverb;

			P_act = (Proverb*)In_Proverb(ifst);

			Assert::AreEqual(P_exp->Country, P_act->Country);
		}
		TEST_METHOD(In_Riddle_Test)
		{
			Riddle* R_exp = new Riddle;

			R_exp->Answer = "Clock";

			ifstream ifst("../AphorismProc/in_riddle.txt");

			Riddle* R_act = new Riddle;

			R_act = (Riddle*)In_Riddle(ifst);

			Assert::AreEqual(R_exp->Answer, R_act->Answer);
		}
		TEST_METHOD(In_Storehouse_Test)
		{
			Storehouse* St_exp = new Storehouse;

			St_exp->K = APHORISM;
			St_exp->Content = "Success is the child of audacity.";
			St_exp->Estimation = 7;
			St_exp->Obj = new Aphorism;
			((Aphorism*)St_exp->Obj)->Author = "Benjamin Disraeli";

			ifstream ifst("../AphorismProc/in_storehouse.txt");

			Storehouse* St_act = new Storehouse;

			St_act = In_Storehouse(ifst);

			Assert::AreEqual((int)St_exp->K, (int)St_act->K);

			Assert::AreEqual(((Aphorism*)St_exp->Obj)->Author, ((Aphorism*)St_act->Obj)->Author);
			Assert::AreEqual(St_exp->Content, St_act->Content);
			Assert::AreEqual(St_exp->Estimation, St_act->Estimation);
		}
		TEST_METHOD(Out_Aphorism_Test)
		{
			Aphorism* A_act = new Aphorism;

			A_act->Author = "Benjamin Disraeli";

			ofstream ofst("../AphorismProc/out_aphorism_act.txt");

			Out_Aphorism(A_act, "Success is the child of audacity.", 7, ofst);

			ifstream ifst_exp("../AphorismProc/out_aphorism_exp.txt");
			ifstream ifst_act("../AphorismProc/out_aphorism_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Out_Proverb_Test)
		{
			Proverb* P_act = new Proverb;

			P_act->Country = "England";

			ofstream ofst("../AphorismProc/out_proverb_act.txt");

			Out_Proverb(P_act, "Two wrongs don't make a right.", 4, ofst);

			ifstream ifst_exp("../AphorismProc/out_proverb_exp.txt");
			ifstream ifst_act("../AphorismProc/out_proverb_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Out_Riddle_Test)
		{
			Riddle* R_act = new Riddle;

			R_act->Answer = "Clock";

			ofstream ofst("../AphorismProc/out_riddle_act.txt");

			Out_Riddle(R_act, "What has a face and two hands but no arms or legs?", 3, ofst);

			ifstream ifst_exp("../AphorismProc/out_riddle_exp.txt");
			ifstream ifst_act("../AphorismProc/out_riddle_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			//Сравниваем
			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Out_Storehouse_Test)
		{
			Riddle* R_act = new Riddle;

			R_act->Answer = "Clock";

			Storehouse* St_act = new Storehouse;

			St_act->K = RIDDLE;
			St_act->Obj = R_act;
			St_act->Content = "What has a face and two hands but no arms or legs?";
			St_act->Estimation = 3;

			ofstream ofst("../AphorismProc/out_storehouse_act.txt");

			Out_Storehouse(St_act, ofst);

			ifstream ifst_exp("../AphorismProc/out_storehouse_exp.txt");
			ifstream ifst_act("../AphorismProc/out_storehouse_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			//Сравниваем
			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Amount_Test)
		{
			Storehouse* St = new Storehouse;

			St->Content = "What has a face and two hands but no arms or legs?";
			St->K = RIDDLE;

			int Amount_exp = 1;
			int Amount_act = Amount_Storehouse(St);

			Assert::AreEqual(Amount_exp, Amount_act);
		}
		TEST_METHOD(Compare_Test)
		{
			Container* Head_First = new Container();

			Head_First->Cont = new Storehouse;
			Head_First->Cont->Content = "What has a face and two hands but no arms or legs?";
			Head_First->Cont->K = RIDDLE;

			Container* Head_Second = new Container();

			Head_Second->Cont = new Storehouse;
			Head_Second->Cont->Content = "Two wrongs don't make a right.";
			Head_Second->Cont->K = PROVERB;

			bool Act = Compare(Head_First, Head_Second);
			bool Exp = false;

			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Sort_Test)
		{
			ifstream ifst("../AphorismProc/input.txt");
			Container* Head = new Container();

			Head = Init(Head);

			In(Head, ifst);

			ofstream ofst("../AphorismProc/sort_act.txt");

			Sort(Head);

			Out(Head, ofst);

			ifstream ifst_exp("../AphorismProc/sort_exp.txt");
			ifstream ifst_act("../AphorismProc/sort_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			Assert::AreEqual(Exp, Act);
		}
	};
}
