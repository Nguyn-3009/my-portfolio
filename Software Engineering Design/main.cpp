#include <iostream>
#include <vector>
#include <regex>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <unordered_map>

#include "AuctionSystem.h"
#include "Guest.h"
#include "Member.h"
#include "Item.h"

using namespace std;

time_t convertToTimeT(const std::string &datetime)
{
  struct tm target_time = {};
  std::istringstream ss(datetime);
  ss >> std::get_time(&target_time, "%d/%m/%Y %H:%M"); // Convert to struct tm

  if (ss.fail())
  {
    throw std::runtime_error("Failed to parse date-time string.");
  }

  return std::mktime(&target_time); // Convert struct tm to time_t
}

string getCurrentTimeString()
{
  auto now = chrono::system_clock::now();                     // Get current time point
  time_t current_time = chrono::system_clock::to_time_t(now); // Convert to time_t (epoch time)
  struct tm *local_time = localtime(&current_time);           // Convert to local time (struct tm)

  // Format the time as "dd/mm/yyyy hh:mm"
  ostringstream time_stream;
  time_stream << put_time(local_time, "%d/%m/%Y %H:%M");

  return time_stream.str(); // Return formatted string
}

auto now = chrono::system_clock::now(); // Get current time
time_t current_time = chrono::system_clock::to_time_t(now);

// Menu of options
void printGuestMenu()
{
  cout << "-----------------\n";
  cout << "This is your menu:\n";
  cout << "1. Sign in\n";
  cout << "2. Sign up\n";
  cout << "3. View items\n";
  cout << "4. Exit\n";
  cout << "Your choice: ";
}

void printAdminMenu()
{
  cout << "-----------------\n";
  cout << "This is your menu:\n";
  cout << "1.  View dashboard\n";
  cout << "2.  Top up credit\n";
  cout << "3.  Change password\n";
  cout << "4.  Change username\n";
  cout << "5.  Search items\n";
  cout << "6.  Place bid\n";
  cout << "7.  Bid\n";
  cout << "8.  Remove bid\n";
  cout << "9.  Set item rating\n";
  cout << "10. Review other member\n";
  cout << "11. Show others review\n";
  cout << "12. View any profile\n";
  cout << "13. Exit\n";
  cout << "Your choice: ";
}

void printMemberMenu()
{
  cout << "-----------------\n";
  cout << "This is your menu:\n";
  cout << "1.  View dashboard\n";
  cout << "2.  Top up credit\n";
  cout << "3.  Change password\n";
  cout << "4.  Change username\n";
  cout << "5.  Search items\n";
  cout << "6.  Place bid\n";
  cout << "7.  Bid\n";
  cout << "8.  Remove bid\n";
  cout << "9.  Set item rating\n";
  cout << "10. Review other member\n";
  cout << "11. Show others review\n";
  cout << "12. Set automatic bid limit" << endl;
  cout << "13. Exit\n";
  cout << "Your choice: ";
}

void handleTransaction(Member *member, AuctionSystem &auctionSystem)
{
  time_t current_time = convertToTimeT(getCurrentTimeString());

  for (const auto &pair : member->getActiveBid())
  {
    Item *itemPtr = pair.first; // Pointer to the Item
    int bidValue = pair.second; // Corresponding bid value

    // handle transaction
    if (convertToTimeT(itemPtr->getEndTime()) < current_time && member->getUsername() == itemPtr->getCurrentBidder()) // check if bid end
    {
      string review;
      cout << "Review this person : "; // review seller
      cin >> review;

      int rate;
      cout << "Rate " << itemPtr->getOwner()->getUsername() << " : "; // rate seller
      cin >> rate;

      if (itemPtr->getOwner()->getReviewsByOthers().size() != 0)
      {
        float newRating = itemPtr->getOwner()->getReviewsByOthers().size() * itemPtr->getOwner()->getRating();
        itemPtr->getOwner()->getReviewsByOthers().push_back(review); // add review

        newRating = (newRating + rate) / itemPtr->getOwner()->getReviewsByOthers().size(); // average rating calculation
        itemPtr->getOwner()->setRating(newRating);                                         // set rating
      }
      else
      {
        itemPtr->getOwner()->getReviewsByOthers().push_back(review);

        float newRating = rate;
        newRating = (newRating + 3) / 2;           // average rating calculation first rate
        itemPtr->getOwner()->setRating(newRating); // set rating
      }

      member->setCP(member->getCP() - itemPtr->getHighestBid());  // minus CP from buyer
      member->getActiveBid().erase(itemPtr);                      // remove bid after transaction
      member->setItemsWonToDate(member->getItemsWonToDate() + 1); // increase items won

      itemPtr->getOwner()->setCP(itemPtr->getOwner()->getCP() + itemPtr->getHighestBid()); // owner get cp from transaction
      for (int i = 0; i < itemPtr->getOwner()->getActiveItemListings().size(); i++)        // remove from active item listing
      {
        if (itemPtr->getOwner()->getActiveItemListings()[i] == itemPtr)
        {
          itemPtr->getOwner()->getActiveItemListings().erase(itemPtr->getOwner()->getActiveItemListings().begin() + i);
          break;
        }
      }

      for (int i = 0; i < auctionSystem.getItems().size(); i++) // remove item from Auction System
      {
        if (auctionSystem.getItems()[i] == itemPtr)
        {
          auctionSystem.getItems().erase(auctionSystem.getItems().begin() + i);
          break;
        }
      }
    }
  }
}

void handleAdmin(Member *member, AuctionSystem &auctionSystem)
{
  handleTransaction(member, auctionSystem);
  string choice;
  do
  {
    choice.clear();

    printAdminMenu(); // print menu options
    getline(cin, choice);

    if (choice == "1")
    {
      member->viewDashBoard();
    }
    else if (choice == "2")
    {
      member->topUpCredit();
    }
    else if (choice == "3")
    {
      member->changePassword(auctionSystem);
    }
    else if (choice == "4")
    {
      member->changeUsername(auctionSystem);
    }
    else if (choice == "5")
    {
      member->proItemSearch(auctionSystem);
    }
    else if (choice == "6")
    {
      member->placeBid(auctionSystem);
    }
    else if (choice == "7")
    {
      member->Bid(auctionSystem);
    }
    else if (choice == "8")
    {
      member->removeBid(auctionSystem);
    }
    else if (choice == "9")
    {
      member->setItemRating();
    }
    else if (choice == "10")
    {
      member->reviewOther(auctionSystem);
    }
    else if (choice == "11")
    {
      member->showReviewsByOther();
    }
    else if (choice == "12")
    {
      member->viewAnyProfile(auctionSystem);
    }
    else if (choice == "13")
    {
      int itemId, limit;
      std::cout << "-----------------\n";
      std::cout << "Enter item ID: ";
      std::cin >> itemId;
      std::cout << "Enter your automatic bid limit: ";
      std::cin >> limit;
      member->setAutoBidLimit(auctionSystem, itemId, limit);
      std::cout << "-----------------\n";
    }
    else if (choice == "14")
    {
      break;
    }
    else
    {
      cout << "Invalid choice" << endl;
    }
  } while (choice != "14");
}

void handleMember(Member *member, AuctionSystem &auctionSystem)
{
  handleTransaction(member, auctionSystem);
  string choice;
  do
  {
    choice.clear();

    printMemberMenu();
    getline(cin, choice);

    if (choice == "1")
    {
      member->viewDashBoard();
    }
    else if (choice == "2")
    {
      member->topUpCredit();
    }
    else if (choice == "3")
    {
      member->changePassword(auctionSystem);
    }
    else if (choice == "4")
    {
      member->changeUsername(auctionSystem);
    }
    else if (choice == "5")
    {
      member->proItemSearch(auctionSystem);
    }
    else if (choice == "6")
    {
      member->placeBid(auctionSystem);
    }
    else if (choice == "7")
    {
      member->Bid(auctionSystem);
    }
    else if (choice == "8")
    {
      member->removeBid(auctionSystem);
    }
    else if (choice == "9")
    {
      member->setItemRating();
    }
    else if (choice == "10")
    {
      member->reviewOther(auctionSystem);
    }
    else if (choice == "11")
    {
      member->showReviewsByOther();
    }
    else if (choice == "12")
    {
      int itemId, limit;
      std::cout << "-----------------\n";
      std::cout << "Enter item ID: ";
      std::cin >> itemId;
      std::cout << "Enter your automatic bid limit: ";
      std::cin >> limit;
      member->setAutoBidLimit(auctionSystem, itemId, limit);
      std::cout << "-----------------\n";
    }
    else if (choice == "13")
    {
      break;
    }
    else
    {
      cout << "Invalid choice" << endl;
    }
  } while (choice != "13");
};

void handleGuest(Guest guest, AuctionSystem &auctionSystem)
{
  string choice;

  do
  {
    printGuestMenu(); // print menu option
    cin >> choice;

    cin.ignore(1, '\n');

    if (choice == "1")
    {
      Member *member = guest.signIn(auctionSystem);

      if (member != nullptr)
      {
        handleMember(member, auctionSystem);
      }
      else
        cout << "Sign In unsucessfully :<" << endl; // unsuccessful signIn
    }
    else if (choice == "2")
    {
      Member *member = guest.signUp(auctionSystem);

      if (member != nullptr)
      {
        handleMember(member, auctionSystem);
      }
      else
        cout << "Sign Up unsucessfully :<" << endl;
    }
    else if (choice == "3")
      guest.limitedItemView(auctionSystem);
    else
      break;
  } while (choice != "4");
}

int main()
{
  AuctionSystem auctionSystem;
  Guest guest;

  auctionSystem.loadData("auction_data.txt");

  // data for testing
  Member *member1 = new Member("Nguyen", "30092004Nguyen!", "VTKN", "0795789411", "vunguyen3009.NGUYEN@gmail.com", "type1", "079204014229");
  Member *member2 = new Member("Nhi", "28072006Nhi!", "NXTN", "0987654321", "vunguyen3009.NGUYEN@gmail.com", "type1", "079204014229");

  Item *item1 = new Item("Coke", "Soda", "Yummm", "14/11/2025 5:00", 10, 3.0, member1);
  Item *item2 = new Item("Iphone", "Electronic Gadgets", "Convenient", "22/8/2023 7:00", 10, 3.0, member1);
  Item *item3 = new Item("PC", "Electronic Gadgets", "Convenient", "22/8/2023 7:00", 20, 3.0, member2);

  auctionSystem.addItem(item1);
  auctionSystem.addItem(item2);
  auctionSystem.addItem(item3);

  auctionSystem.addMember(member1);
  auctionSystem.addMember(member2);

  auctionSystem.turnAdmin(member1);

  cout << "EEET2482/COSC2081 GROUP ASSIGNMENT" << endl;
  cout << "Semester C 2024" << endl;
  cout << "AUCTION APPLICATION" << endl;
  cout << endl;
  cout << "Instructor: Dr Ling Huo Chong" << endl;
  cout << "Group: Group No.5" << endl;
  cout << "sID: s3979209, Student Name: Khang Nguyen Huynh Gia" << endl;
  cout << "sID: s3978646, Student Name: Kiet Le Tuan" << endl;
  cout << "sID: s3981122, Student Name: Khoi Dinh Dang" << endl;
  cout << "sID: s3978262, Student Name: Nguyen Vu Tran Khoi" << endl;
  cout << endl;

  string choice;

  // main function of application
  do
  {
    choice.clear();
    cout << "-----------------\n";
    cout << "Enter choice : 1. Guest 2. Member 3. Admin 4.Exit\n";
    cout << "your choice : ";
    getline(cin, choice);
    cout << "-----------------\n";
    if (choice == "1")
    {
      handleGuest(guest, auctionSystem);
    }
    else if (choice == "2")
    {
      Member *member = guest.signIn(auctionSystem);

      if (member != nullptr)
      {
        handleMember(member, auctionSystem);
      }
      else
        cout << "Sign In unsucessfully :<" << endl;
    }
    else if (choice == "3")
    {
      Member *member = guest.signInAdmin(auctionSystem);

      if (member != nullptr)
      {
        handleAdmin(member, auctionSystem);
      }
      else
      {
        cerr << "Sign In unsuccessfully :< you are not an admin" << endl;
      }
    }
    else if (choice == "4")
    {
      auctionSystem.saveData("auction_data.txt");
      return 0;
    }

    else
      cerr << "Invalid choice" << endl;
  } while (choice != "4");
  return 0;
}