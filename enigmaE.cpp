//Incuding the libraries for input and output
#include <iostream>

//tells the compiler for functions like cin, cout etc. to be looked from std directory
using namespace std;

//2D array to create plugboard pairs for switching
string pbc[2][10];

//3D array to create rotor shifting pairs for 6 rotors
string rotor[6][2][26] = { { { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" },{"Q", "M", "A", "T", "Z", "L", "E", "N", "U", "D", "Y", "H", "K", "B", "W", "O", "J", "R", "C", "G", "F", "X", "I", "S", "P", "V"} }, { { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" }, { "B", "X", "E", "U", "N", "P", "S", "Y", "C", "K", "G", "T", "O", "H", "Z", "R", "D", "W", "L", "F", "Q", "I", "J", "A", "V", "M" } },{{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" },{"J", "T", "E", "M", "B", "I", "Z", "W", "F", "C", "L", "X", "P", "U", "D", "S", "G", "H", "Y", "A", "K", "R", "Q", "O", "V", "N"}},{ { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" },{"C", "W", "H", "O", "E", "R", "X", "B", "L", "G", "I", "A", "T", "F", "N", "Z", "M", "Y", "J", "U", "D", "K", "V", "S", "P", "Q"}},{{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" },{"V", "M", "U", "K", "T", "Y", "H", "P", "E", "J", "Z", "G", "A", "O", "S", "B", "C", "F", "W", "I", "D", "N", "L", "Q", "X", "R"}},{{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" },{"F", "Y", "U", "C", "E", "T", "H", "X", "B", "R", "W", "I", "K", "M", "L", "Z", "D", "J", "A", "V", "G", "S", "P", "Q", "N", "O"}} };

//1D array to store rotor offset from the main value they point out to be
int rotorS[6];

//letters lowercase to uppercase
void standard(string& in) {
	for (int i = 0; i < in.length(); i++) {
		if ((int)in[i]<123 && (int)in[i]>96) {
			in[i] = (char)((int)in[i] - 32);
		}
	}
}

//letters uppercase to lowercase
void destandardizer(string& in) {
	for (int i = 0; i < in.length(); i++) {
		if ((int)in[i] < 91 && (int)in[i]>64) {
			in[i] = (char)((int)in[i] + 32);
		}
	}
}

//Entering the plugboard pairs
void enterPlugboard() {
	cout << endl;
	cout << "Enter the plugboard combinations (10) in the format, " << endl << "1st letter: X" << endl << "2nd letter: Y" << endl<<endl;
	cout << "****** NOTE: the rest of the letters would remain unpaired ! ******"<<endl<<endl;

	for (int i = 0; i < 10; i++) {
		bool check = 1;
		while (check) {
			string l1, l2;
			cout << "1rst letter: ";
			getline(cin, l1);
			cout << "2nd letter: ";
			getline(cin, l2);
			cout << endl;

			standard(l1);
			standard(l2);

			if ((int)(l1[0]) < 91 && (int)(l1[0]) > 64 && (int)(l2[0]) < 91 && (int)(l2[0]) > 64 && l1.length()==1 && l2.length()==1 && l1!=l2) {
				if (i>0) {
					for (int j = 0; j < i; j++) {
						if (l1 == pbc[0][j] || l1 == pbc[1][j] || l2 == pbc[0][j] || l2 == pbc[1][j]) {
							cerr << "The same letter can't be paired twice !!" << endl << "Scroll above to check already formed pairs..." << endl << endl;
						}
						else {
							pbc[0][i] = l1;
							pbc[1][i] = l2;
							check = 0;
						}
					}
				}
				else {
					pbc[0][i] = l1;
					pbc[1][i] = l2;
					check = 0;
				}
			}
			else {
				cerr << "Enter a valid entry pair!!" << endl << endl;
			}
		}
	}
}

//Entering the rotor shifts
void setupRotors() {
	cout << endl << endl;
	cout << "Enter the rotor configuration in the format, " << endl << "1rst shift: 0 & so on till the 6th rotor ;"<< endl;
	cout << "****** NOTE: Nth shift indicates that the rotor shifts the letter corresponding to entry by the value provided******" << endl << endl;

	for (int i = 0; i < 6; i++) {
		bool check = 1;
		while (check) {
			cout << "Shift " << i + 1 << ": ";
			string n;
			getline(cin, n);

			if (n.length()) {
				bool intcheck = 1;
				for (int i = 0; i < n.length(); i++) {
					if (((int)(n[i]) > 57 || (int)(n[i]) < 48) && intcheck == 1) {
						cout << "Enter a number !! " << endl << endl;
						intcheck = 0;
					}
				}
				if (intcheck == 1) {
					rotorS[i] = stoi(n) % 26;
					check = 0;
				}
			}
			else {
				clog << "Enter a non null type entry!!"<<endl<<endl;
			}
		}
	}
}

//Swithcing the values as per entries in plugboard
void plugboardShift(string& in) {
	for (int i = 0; i < in.length() ;i++) {
		for (int j = 0; j < 10; j++) {
			if (in[i] == (pbc[0][j])[0])
				in[i] = (pbc[1][j])[0];
			else if (in[i] == (pbc[1][j])[0])
				in[i] = (pbc[0][j])[0];
		}
	}
}

//Switching the values as per rotors and updating the shift value accordingly
void rotEncrypt(string& in) {
	for (int i = 0;i<in.length();i++) {
		for (int j = 0; j < 6; j++) {
			bool updated = 0;
			for (int k = 0; k < 26; k++) {
				if (in[i]==(rotor[j][0][k])[0] && updated==0) {
					in[i] = (rotor[j][1][((k + rotorS[j]) % 26)])[0];
					updated = 1;
				}
			}
		}
		rotorS[0] = (rotorS[0]+1)%26;
		(i + 1) % 26 == 0 ? rotorS[1] = (rotorS[1] + 1) % 26 : rotorS[1] += 0;
		(i + 1) % 576 == 0 ? rotorS[2] = (rotorS[2] + 1) % 26 : rotorS[2] += 0;
		(i + 1) % 17576 == 0 ? rotorS[3] = (rotorS[3] + 1) % 26 : rotorS[3] += 0;
		(i + 1) % 456976 == 0 ? rotorS[4] = (rotorS[4] + 1) % 26 : rotorS[4] += 0;
		(i + 1) % 11881376 == 0 ? rotorS[5] = (rotorS[5] + 1) % 26 : rotorS[5] += 0;
	}
}

//Switching the values as per rotors and updating the shift value accordingly but in reverse
void rotDecrypt(string& in) {
	for (int i = 0; i < in.length(); i++) {
		for (int j = 6; j >= 0; j--) {
			bool updated = 0;
			for (int k = 0; k < 26; k++) {
				if (in[i] == (rotor[j][1][k])[0] && updated == 0) {
					in[i] = (rotor[j][0][(k - rotorS[j] < 0 ? k - rotorS[j] + 26 : k - rotorS[j])])[0];
					updated = 1;
				}
			}
		}
		rotorS[0] = (rotorS[0] + 1) % 26;
		(i + 1) % 26 == 0 ? rotorS[1] = (rotorS[1] + 1) % 26 : rotorS[1] += 0;
		(i + 1) % 576 == 0 ? rotorS[2] = (rotorS[2] + 1) % 26 : rotorS[2] += 0;
		(i + 1) % 17576 == 0 ? rotorS[3] = (rotorS[3] + 1) % 26 : rotorS[3] += 0;
		(i + 1) % 456976 == 0 ? rotorS[4] = (rotorS[4] + 1) % 26 : rotorS[4] += 0;
		(i + 1) % 11881376 == 0 ? rotorS[5] = (rotorS[5] + 1) % 26 : rotorS[5] += 0;
	}
}

int main() {
	cout << "*********************************************************************" << endl;
	cout << "******************* Welcome to the enigma model E *******************" << endl;
	cout << "*********************************************************************" << endl << endl;
	cout << "Choose to get into encryption or decryption mode respectively (e/d): ";

	string mode;
	string input;
	getline(cin, mode);
	cout << endl;

	//Entering the encryption mode
	if (mode == "e") {
		cout << "Welcome to the encryption mode ! ," << endl << "Please enter the message you want to encrypt: ";
		getline(cin, input);    /*getting the input*/
		standard(input);
		
		enterPlugboard();
		setupRotors();

		plugboardShift(input);
		rotEncrypt(input);
		plugboardShift(input);

		cout <<endl<< "The encrypted message is: \"" << input << "\" .\n\n"<<"********* WARNING: don't use any other part of output except the one in \"-\" as encrypted message *********\n";   /*presenting the encrytped message*/
	}

	//Entering the decryption mode
	else if (mode == "d") {
		cout << "Welcome to the decryption mode ! ;" << endl << "Please enter the message you want to decrypt: ";
		getline(cin, input);	/*getting the input*/
		standard(input);

		enterPlugboard();
		setupRotors();

		plugboardShift(input);
		rotDecrypt(input);
		plugboardShift(input);
		destandardizer(input);

		cout << endl << "The decrypted message is: \"" << input << "\" .\n\n" ;	/*presenting the decrypted message*/
	}

	//Handling the wrong entry by user
	else {
		cout << "Invalid mode of operation !";
	}
}