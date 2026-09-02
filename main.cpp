#include <iostream>


//商品データ
class ITEM
{
public:
  ITEM():mId(0),mName(""),mPrice(0)
  {
    ;
  }

  int mId;
  std::string mName;
  int mPrice;
};

using ItemId = int;

//商品管理
class ITEM_LIST
{
private:
  ItemId mNextItemId = 0;
  std::vector<ITEM> mItemLists;

  ItemId GenerateItemId()
  {
    mNextItemId++;
    return mNextItemId;
  }
public:
  //商品追加
  void AddItem()
  {
    //int newItemId = GenerateItemId();
  }
  //商品一覧を表示する
  void DisplayItemList()
  {
  }
  //IDから商品を検索する
  // ITEM SerchItemFromId() const
  // {
  //   ITEM item;
  //   return item;
  // }
  //IDを指定して商品を削除する
  // void RemoveItemFromId( ItemId id )
  // {
  //   ;
  // }
  //価格順に商品を表示する
  void DisplaySortedPriceItemList()
  {
  }
};



int main()
{
  std::cout<<"hello item-manager"<<'\n';
  int count=0;
  while(1){
    std::cout<<"count:"<<count<<" command?"<<'\n';
    count++;
    int input = 0;
    std::cin>>input;
    if( input >= 0 ){
      break;
    }
    std::cout<<"item-manager is end\n";
  }

  return 0;
}
  //


