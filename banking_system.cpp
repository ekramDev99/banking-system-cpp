#include <iostream>
#include<string>
#include <iomanip>
#include<cmath>
#include<vector>
#include<fstream>
#include <ctime>
#include<cctype>
using namespace std;
void ShowTransactionMenu();
void Login();
void  ShowUsersMenu();
//void BackToMainMenu();
void ShowMainMenu();
const string ClientsFile = "Clients.txt";
const string UsersFile = "Users.txt";
enum enMainMenuOption { eShowClients = 1, eAddNewClients = 2, eDeleteClients = 3, eUpdateClients = 4, eFindClients = 5, eTransactions = 6, eMangesUser = 7, eLogout = 8 };
enum enTransactionMenu { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenu = 4 };
enum enUsersMenuOptition { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenuUser = 6 };
enum enMainMenuPermissions { eAll = -1, PListClient = 1, PAddNewClient = 2, PDeleteClient = 4, PUpdateClient = 8, PFindClient = 16, PTransaction = 32, PMangeUsers = 64 };




struct stClient {
	string AccountNumber;
	string PinCode;
	string PhoneNumber;
	string Name;
	double AccountBalance;
	bool MarkForDelete = false;

};
struct stUsers {
	string Admin;
	string Password;
	int Permissions;
	bool MarkForDelete = false;


};

stUsers CurrentUser;


vector <string> Split(string S1, string Delim) {
	vector <string> vString;
	int Pos = 0;
	string sWord;
	while ((Pos = S1.find(Delim)) != std::string::npos) {
		sWord = S1.substr(0, Pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}
		S1.erase(0, Pos + Delim.length());
	}
	if (S1 != "") {

		vString.push_back(S1);
	}
	return vString;
}
stUsers ConvertLinetoRecordForUsers(string Line, string Seperator = "#//#")

{
	stUsers User;
	vector<string> vUsers;
	vUsers = Split(Line, Seperator);
	User.Admin = vUsers[0];
	User.Password = vUsers[1];
	User.Permissions = stoi(vUsers[2]);
	return User;
}
vector <stUsers> LoadUserDataFromFile(string FileName)
{
	vector <stUsers> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stUsers Users;
		while (getline(MyFile, Line))
		{

			Users = ConvertLinetoRecordForUsers(Line);
			vUsers.push_back(Users);
		}
		MyFile.close();
	}

	return vUsers;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")

{
	stClient Client;
	vector<string> vClientData;
	vClientData = Split(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.PhoneNumber = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

vector <stClient> LoadCleintsDataFromFile(string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Contact Your Admin.";
	cout << "\n------------------------------------\n";
}

bool CheckAccessPermissions(enMainMenuPermissions Permission) {
	if (CurrentUser.Permissions == enMainMenuPermissions::eAll)
		return true;
	if ((CurrentUser.Permissions & Permission) == Permission)
		return true;
	else
		return false;
}
void PrintClientRecord(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.PhoneNumber;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintUsersRecord(stUsers User)
{
	cout << "| " << setw(15) << left << User.Admin;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;

}
void PrintAllClientsData()
{
	if (!CheckAccessPermissions(enMainMenuPermissions::PListClient)) {
		ShowAccessDeniedMessage();
		return;
	}
	vector<stClient> vClients;
	vClients = LoadCleintsDataFromFile(ClientsFile);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")	Client(s).";

	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0) {
		cout << "\t\t\t\t No Clients Available In System\n";
	}
	for (stClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void PrintAllUsersData()
{

	vector<stUsers> vUsers;
	vUsers = LoadUserDataFromFile(UsersFile);
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ")	User(s).";

	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Admin";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permision";

	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vUsers.size() == 0) {
		cout << "\t\t\t\t No Users Available In System\n";
	}
	for (stUsers Users : vUsers)
	{
		PrintUsersRecord(Users);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
bool ClientExistsByAccountNumber(string FileName, string AccountNumber)
{

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);

			if (Client.AccountNumber == AccountNumber) {
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}
	return false;

}

stClient ReadNewClient()
{
	stClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(ClientsFile, Client.AccountNumber)) {
		cout << "Account [" << Client.AccountNumber << "] Already Exists Enter Another Account Number ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")

{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.PhoneNumber + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
string ConvertUserRecordToLine(stUsers User, string Seperator = "#//#")

{
	string stUserRecord = "";
	stUserRecord += User.Admin + Seperator;
	stUserRecord += User.Password + Seperator;
	stUserRecord += to_string(User.Permissions);
	return stUserRecord;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFile, ConvertRecordToLine(Client));

}
void AddClients()
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";

		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientScreen() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PAddNewClient)) {
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n--------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n--------------------------------\n";
	AddClients();
}
bool FindUserByName(string FileName, string Admin) {
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stUsers Users;
		while (getline(MyFile, Line))
		{
			Users = ConvertLinetoRecordForUsers(Line);

			if (Users.Admin == Admin) {
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}
	return false;


}
int ReadPermissionsToSet() {
	int Permission = 0;
	char Answer = 'n';
	cout << "do you want to give full access?\n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		return -1;
	}
	cout << "\ndo you want to give access to :\n";
	cout << "Show Clients Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PListClient;
	}
	cout << "Add New Clients Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PAddNewClient;
	}
	cout << "Delete Clients Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PDeleteClient;
	}
	cout << "Update Clients Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PUpdateClient;
	}
	cout << "Find Clients Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PFindClient;
	}
	cout << "Transaction Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PTransaction;
	}
	cout << "Manage User Y/N? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permission += enMainMenuPermissions::PMangeUsers;
	}
	return Permission;

}
stUsers ReadNewUser() {
	stUsers User;

	cout << "Enter UserName\n";
	getline(cin >> ws, User.Admin);
	while (FindUserByName(UsersFile, User.Admin)) {
		cout << "Already exists [" << User.Admin << "] please enter another one\n";
		getline(cin, User.Admin);
	}
	cout << "Enter Password\n";
	cin >> User.Password;
	User.Permissions = ReadPermissionsToSet();

	return User;
}

void AddNewUser() {
	stUsers User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFile, ConvertUserRecordToLine(User));

}
void AddNewUsers() {
	char AddMore = 'Y';


	do {
		cout << "Add New User\n";
		AddNewUser();
		cout << "Users Added Sucssfully Do You Want To Add More Users Y/N?\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddNewUserScreen() {

	cout << "\n--------------------------------\n";
	cout << "\tAdd New Users Screen";
	cout << "\n--------------------------------\n";
	AddNewUsers();
}

void PrintClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.PhoneNumber;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}
void PrintUserCard(stUsers User)
{
	cout << "\nThe following are the User details:\n";
	cout << "\nUser Name: " << User.Admin;
	cout << "\nPassword : " << User.Password;
	cout << "\nPermissions : " << User.Permissions;

}


bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)

{
	for (stClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;

		}
	}
	return false;
}
bool FindUserByUserName(string UserName, vector <stUsers> vUsers, stUsers& User)

{
	for (stUsers U : vUsers)
	{
		if (U.Admin == UserName)
		{
			User = U;
			return true;

		}
	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByUserName(string UserName, vector <stUsers>& vUsers)
{

	for (stUsers& U : vUsers)
	{
		if (U.Admin == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)

{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.

				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector <stUsers> SaveUsersDataToFile(string FileName, vector <stUsers> vUsers)

{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (stUsers U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.

				DataLine = ConvertUserRecordToLine(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)


{
	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFile, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFile);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

		return false;
	}
}
bool DeleteUsersByUserName(string UserName, vector <stUsers>& vUsers)


{
	stUsers User;
	char Answer = 'n';
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want delete this User? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveUsersDataToFile(UsersFile, vUsers);
			//Refresh Clients
			vUsers = LoadUserDataFromFile(UsersFile);
			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with Name (" << UserName << ") is Not Found!";

		return false;
	}
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
string ReadUserName()
{
	string UserName = "";
	cout << "\nPlease enter User-Name? ";
	cin >> UserName;
	return UserName;
}
void ShowDeleteScreenForUser() {

	cout << "\n--------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n--------------------------------\n";
	vector <stUsers> vUsers = LoadUserDataFromFile(UsersFile);
	string UserName = ReadUserName();
	DeleteUsersByUserName(UserName, vUsers);
}
void ShowDeleteScreen() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PDeleteClient)) {
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n--------------------------------\n";
	cout << "\tDelete Clients Screen";
	cout << "\n--------------------------------\n";
	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

stUsers ChangeUsersRecord(string UserName)
{
	stUsers User;
	User.Admin = UserName;
	cout << "\n\nEnter Password? ";
	getline(cin >> ws, User.Password);
	User.Permissions = ReadPermissionsToSet();
	return User;
}
bool UpdateUserByUserName(string UserName, vector <stUsers>& vUser)

{
	stUsers User;
	char Answer = 'n';
	if (FindUserByUserName(UserName, vUser, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want update this User? y/n ? ";

		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stUsers& U : vUser)
			{
				if (U.Admin == UserName)
				{
					U = ChangeUsersRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UsersFile, vUser);
			cout << "\n\nUsers Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!";

		return false;
	}
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)

{
	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";

		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFile, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

		return false;
	}
}
void ShowUpdateScreenForUsers() {

	cout << "\n--------------------------------\n";
	cout << "\tUpdate Userss Screen";
	cout << "\n--------------------------------\n";

	vector <stUsers> vUsers = LoadUserDataFromFile(UsersFile);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUsers);
}
void ShowUpdateScreen() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PUpdateClient)) {
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n--------------------------------\n";
	cout << "\tUpdate Clients Screen";
	cout << "\n--------------------------------\n";

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowFindUsersScreen() {

	cout << "\n--------------------------------\n";
	cout << "\tFind Users Screen";
	cout << "\n--------------------------------\n";
	stUsers User;
	vector <stUsers> vUsers = LoadUserDataFromFile(UsersFile);
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);
	}
	else {
		cout << "\nUsers with UserName [" << UserName << "] is not found!";
	}

}
void ShowFindClientScreen() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PFindClient)) {
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n--------------------------------\n";
	cout << "\tFind Clients Screen";
	cout << "\n--------------------------------\n";
	stClient Client;
	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}

	else {
		cout << "\nClients with Account [" << AccountNumber << "] is not found!";
	}

}
void ShowExitScreen() {

	cout << "\n--------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n--------------------------------\n";
}
void BackToMainMenu() {

	cout << "Press any key to back to main menu ";
	system("pause");

	ShowMainMenu();
}
short ReadChoiceOption() {
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 8]?\n";
	cin >> Choice;
	return Choice;
}
short ReadChoiceTransaction() {
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 4]?\n";
	cin >> Choice;
	return Choice;
}
short ReadUserChoice() {
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 6]?\n";
	cin >> Choice;
	return Choice;
}
void BackToTransactionMenu() {
	cout << "\n\n Press Any Key To Go Back To Transaction Menu...";
	system("pause");
	ShowTransactionMenu();
}
void BackToUsersMenu() {
	cout << "\n\n Press Any Key To Go Back To Users Menu...";
	system("pause");
	ShowUsersMenu();
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients) {

	char Answer = 'n';


	cout << "\n\nAre Yoy Sure you want perform this transaction y/n?\n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {

		for (stClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				cout << "\n\n Done Succssfully. New Balance is " << C.AccountBalance;
				SaveCleintsDataToFile(ClientsFile, vClients);
				return true;
			}
		}

	}
	return false;



}
void ShowDepositScreen() {
	cout << "\n--------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n--------------------------------\n";
	stClient Client;
	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "Account [" << AccountNumber << "] is not found\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\n\nplease enter deposit Amount \n";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);




}
void ShowWithdrawScreen() {
	cout << "\n--------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n--------------------------------\n";
	stClient Client;
	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "Account [" << AccountNumber << "] is not found\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\n\nplease enter Withdraw Amount \n";
	cin >> Amount;
	while (Amount > Client.AccountBalance) {
		cout << "\n Amount Exceeds the balance,you can withdraw up to : " << Client.AccountBalance;
		cout << "\nPlease enter Another Amount\n";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);




}
void PrintClientRecordBalanceLine(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowTotalBalances()
{

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFile);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ")	Client(s).";


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;

			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}
bool FindUsersByUserNameAndPassword(string UserName, string Password, stUsers& User) {
	vector <stUsers> vsUsers = LoadUserDataFromFile(UsersFile);
	for (stUsers U : vsUsers) {
		if (U.Admin == UserName && U.Password == Password) {
			User = U;
			return true;
		}

	}
	return false;
}
bool LoadUserInfo(string UserName, string Password) {
	if (FindUsersByUserNameAndPassword(UserName, Password, CurrentUser))
		return true;
	else
		return false;
}
void PerformTransactionOption(enTransactionMenu TransactionMenu) {
	switch (TransactionMenu) {
	case enTransactionMenu::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		BackToTransactionMenu();
		break;
	}
	case enTransactionMenu::eWithdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		BackToTransactionMenu();
		break;
	}
	case enTransactionMenu::eTotalBalances:
	{
		system("cls");
		ShowTotalBalances();
		BackToTransactionMenu();
		break;
	}
	case enTransactionMenu::eMainMenu:
	{
		ShowMainMenu();
		break;
	}

	}

}
void ShowTransactionMenu() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PTransaction)) {
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t\tTrasactions Menu Screen\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balnaces.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";

	PerformTransactionOption((enTransactionMenu)ReadChoiceTransaction());

}

void PerformMainMenuOption(enMainMenuOption MainMenu) {
	switch (MainMenu) {
	case enMainMenuOption::eShowClients:
	{

		system("cls");
		PrintAllClientsData();
		BackToMainMenu();
		break;
	}
	case enMainMenuOption::eAddNewClients:
	{

		system("cls");
		ShowAddNewClientScreen();
		BackToMainMenu();
		break;
	}
	case enMainMenuOption::eDeleteClients:
	{

		system("cls");
		ShowDeleteScreen();
		BackToMainMenu();
		break;
	}
	case enMainMenuOption::eUpdateClients:
	{

		system("cls");
		ShowUpdateScreen();
		BackToMainMenu();
		break;
	}

	case enMainMenuOption::eFindClients:
	{

		system("cls");
		ShowFindClientScreen();
		BackToMainMenu();
		break;


	}
	case enMainMenuOption::eTransactions:
	{


		system("cls");
		ShowTransactionMenu();

		break;


	}
	case enMainMenuOption::eMangesUser:
	{

		system("cls");
		ShowUsersMenu();

		break;


	}


	case enMainMenuOption::eLogout:
	{

		system("cls");

		Login();
		break;
	}
	}

}

void ShowMainMenu() {
	system("cls");
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t\t Main Menu Screen\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction Menu.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";

	PerformMainMenuOption((enMainMenuOption)ReadChoiceOption());

}
void PerformUsersOption(enUsersMenuOptition UsersMenu) {
	switch (UsersMenu) {
	case enUsersMenuOptition::eListUsers:
	{
		system("cls");
		PrintAllUsersData();
		BackToUsersMenu();
		break;

	}
	case enUsersMenuOptition::eAddNewUser:
	{
		system("cls");
		ShowAddNewUserScreen();
		BackToUsersMenu();
		break;
	}
	case enUsersMenuOptition::eDeleteUser:
	{
		system("cls");
		ShowDeleteScreenForUser();
		BackToUsersMenu();
		break;

	}
	case enUsersMenuOptition::eUpdateUser:
	{
		system("cls");
		ShowUpdateScreenForUsers();
		BackToUsersMenu();
		break;
	}
	case enUsersMenuOptition::eFindUser:
	{
		system("cls");
		ShowFindUsersScreen();
		BackToUsersMenu();
		break;
	}
	case enUsersMenuOptition::eMainMenuUser:
	{
		system("cls");

		ShowMainMenu();
		break;
	}
	}

}

void ShowUsersMenu() {
	if (!CheckAccessPermissions(enMainMenuPermissions::PMangeUsers)) {
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t\tUsers Menu Screen\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	PerformUsersOption((enUsersMenuOptition)ReadUserChoice());

}



void Login() {
	bool LoginFalied = false;
	string UserName, Password;

	do {
		system("cls");
		cout << "\n--------------------------------\n";
		cout << "\t   Login Screen";
		cout << "\n--------------------------------\n";
		if (LoginFalied) {
			cout << "Invalid UserName/Password\n";
		}
		cout << "please Enter a UserName?\n";
		cin >> UserName;
		cout << "please Enter a Password?\n";
		cin >> Password;
		LoginFalied = !LoadUserInfo(UserName, Password);

	} while (LoginFalied);

	ShowMainMenu();
}


int main()
{

	Login();

	system("pause>0");
	return 0;
}

