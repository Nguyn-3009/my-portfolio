// Guest.h
#ifndef GUEST_H
#define GUEST_H

class Member;
class AuctionSystem;

class Guest
{
public:
  void limitedItemView(AuctionSystem &auctionSystem);
  Member *signIn(AuctionSystem &auctionSystem);
  Member *signInAdmin(AuctionSystem &auctionSystem);
  Member *signUp(AuctionSystem &auctionSystem);
};

#endif // GUEST_H