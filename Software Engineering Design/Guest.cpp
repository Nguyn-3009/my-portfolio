// Guest.cpp
#include <string>
#include <iostream>
#include <iomanip>

#include "Member.h"
#include "Guest.h"
#include "AuctionSystem.h"

using namespace std;

void Guest::limitedItemView(AuctionSystem &auctionSystem)
{
  string itemName;
  cout << "Enter item name : ";
  cin >> itemName;

  cout << "Matching items : " << endl;
  cout << "---------------------------------------------------" << endl;
  for (Item *item : auctionSystem.getItems())
  {
    // view item with limited info
    if ((itemName.empty() || item->getItemName().find(itemName) != string::npos) && item->getRatingScore() <= 3)
    {
      cout << setw(20) << left << "Item name: " << item->getItemName() << endl;
      cout << setw(20) << left << "Item category: " << item->getCategory() << endl;
      cout << setw(20) << left << "Item description: " << item->getDescription() << endl;
      cout << "---------------------------------------------------" << endl;
    }
  }
}

Member *Guest::signIn(AuctionSystem &auctionSystem)
{
  if (auctionSystem.getMembers().size() == 0)
  {
    cout << "No account in this system yet" << endl;
    return nullptr;
  }

  string username;
  cout << "Enter username: ";
  getline(cin, username);

  string password;
  cout << "Enter password: ";
  getline(cin, password);

  for (Member *member : auctionSystem.getMembers())
  {
    if (member->getUsername() == username && member->getPassword() == password) // check username, password for sign in
    {
      cout << "Sign In successfully !" << endl;
      member->viewDashBoard();

      return member;
    }
  }

  return nullptr;
}

Member *Guest::signInAdmin(AuctionSystem &auctionSystem)
{
  if (auctionSystem.getMembers().size() == 0)
  {
    cout << "No account in this system yet" << endl;
    return nullptr;
  }

  string username;
  cout << "Enter username: ";
  getline(cin, username);

  string password;
  cout << "Enter password: ";
  getline(cin, password);

  for (Member *member : auctionSystem.getMembers())
  {
    if (member->getUsername() == username && member->getPassword() == password && member->getIsAdmin() == 1) // same with signIn but check whether he is admin or not
    {
      cout << "Sign In successfully !" << endl;
      member->viewDashBoard();

      return member;
    }
  }

  return nullptr;
}

Member *Guest::signUp(AuctionSystem &auctionSystem)
{
  string username;
  string password;

  cin.ignore(1, '\n');

  do
  {
    username.clear();
    cout << "Enter username: ";
    getline(cin, username);

    if (auctionSystem.getMembers().size() == 0)
    {
      break;
    }

  } while (auctionSystem.isUsernameTaken(username)); // username policy

  do
  {
    password.clear();

    cout << "Enter password: ";
    getline(cin, password);

  } while (!auctionSystem.isValidPassword(password)); // password policy


  // fill in account info for new account
  string fullName;
  cout << "Enter full name: ";
  getline(cin, fullName);

  string phonenumber;
  cout << "Enter phone number: ";
  getline(cin, phonenumber);

  string email;
  cout << "Enter email: ";
  getline(cin, email);

  string IDtype;
  cout << "Enter ID type: ";
  getline(cin, IDtype);

  string IDnumber;
  cout << "Enter ID number: ";
  getline(cin, IDnumber);

  Member *newMember = new Member(username, password, fullName, phonenumber, email, IDtype, IDnumber);

  newMember->viewDashBoard();

  auctionSystem.addMember(newMember);
  return newMember;
}