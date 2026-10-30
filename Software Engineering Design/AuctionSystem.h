// AuctionSystem.h
#ifndef AUCTIONSYSTEM_H
#define AUCTIONSYSTEM_H

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include "Item.h"
#include "Member.h"

class AuctionSystem
{
private:
  std::vector<Item *> items;
  std::vector<Member *> members;

public:
  std::vector<Item *> &getItems();
  std::vector<Member *> &getMembers();

  bool isUsernameTaken(const std::string &username);
  bool isValidPassword(const std::string &password);
  bool checkUserName(std::string username);

  void saveData(const std::string &filename);
  void loadData(const std::string &filename);
  void addMember(Member *member);
  void addItem(Item *item);
  void removeItem(Item *item);
  void turnAdmin(Member *member);
};

#endif // AUCTIONSYSTEM_H