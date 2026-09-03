#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

//商品ID
using ItemId = int;


//商品データ
class Item
{
public:

  Item(ItemId id, std::string name, int price)
  {
    mId = id;
    mName = std::move(name);
    mPrice = price;
  }

  ItemId mId;
  std::string mName;
  int mPrice;
};


//商品管理
class ItemList
{
private:
  ItemId mNextItemId = 0;
  std::vector<Item> mItemLists;

  ItemId GenerateItemId()
  {
    mNextItemId++;
    return mNextItemId;
  }

public:
  
//商品追加
  ItemId AddItem( std::string name, int price )
  {
    ItemId itemId = GenerateItemId();
    // Item item = {itemId,name,price};
    mItemLists.emplace_back( itemId, std::move(name), price );
    return itemId;
  }
  
  //商品一覧を表示する
  void DisplayItemList()const
  {
      for( const Item& item : mItemLists ){
        std::cout<<"ID:"<<item.mId<<" name:"<<item.mName<<" price "<<item.mPrice<<'\n';
      }
  }

  //IDから商品を検索する
  const Item *SearchItemById( ItemId id ) const
  {
    auto it = std::find_if(
      mItemLists.begin(),
      mItemLists.end(),
      [id](const Item& a)
      {
        return id == a.mId;
      }
    );
    if( it != mItemLists.end() ){
      return &(*it);
    }
    return nullptr;
  }
  //IDを指定して商品を削除する
  bool RemoveItemById( ItemId id )
  {
    auto newEnd = std::remove_if(
      mItemLists.begin(),
      mItemLists.end(),
      [id]( const Item& a)
      {
        return id == a.mId;
      }
    );
    if( newEnd == mItemLists.end() )
    {
      return false;
    }
    mItemLists.erase( newEnd, mItemLists.end() );
    return true;
  }

  //価格順に商品を表示する
  void DisplaySortedItemListByPrice()const
  {
    std::vector<const Item*> list;
    for( const Item &item : mItemLists)
    {
        list.push_back( &item );
    }
    std::sort(
      list.begin(),
      list.end(),
      [](const Item *a, const Item *b)
      {
        return a->mPrice < b->mPrice;
      }
    );

    for( const Item *item : list )
    {
      std::cout<<"Id "<<item->mId<<" "<<item->mName<<" "<<item->mPrice<<"\n";
    }
  }
};



int main()
{
  std::cout<<"hello item-manager"<<'\n';

  ItemList itemList;
  itemList.AddItem( "apple",100);
  itemList.AddItem("grape", 150);
  itemList.AddItem("banana", 80);

  while(1){
    std::cout<<"\n";
    std::cout<<"--Menu--\n";
    std::cout<<" 1:add item\n";
    std::cout<<" 2:display list\n";
    std::cout<<" 3:search by id\n";
    std::cout<<" 4:remove by id\n";
    std::cout<<" 5:Display Sorted list by price\n";
    std::cout<<" 0:End\n\n";
    std::cout<<" command? ";
    //count++;
    int input = 0;
    std::cin>>input;

    bool exit = false;
    switch(input)
    {
      default://不正な値
        std::cout<<"iligal command no:"<<input<<'\n';
        break;

      case 0://終了
        exit = true;
        break;

      case 1://商品追加
        {
          std::cout<<"name?";
          std::string name;
          std::cin>>name;
          std::cout<<"price?";
          int price=0;
          std::cin>>price;
          ItemId id = itemList.AddItem( name, price );
          std::cout<<"item add id:" << id<<"\n";
        }
        break;

      case 2://リスト表示
        itemList.DisplayItemList();
        std::cout<<"\n";
        break;

      case 3://ID検索
        {
          ItemId id;
          std::cout<<"Input search id:";
          std::cin>>id;
          const Item *item = itemList.SearchItemById( id );
          if( item != nullptr)
          {
            std::cout<<"find!\n";
            std::cout<<"id:"<<id<<" "<<item->mName <<" "<<item->mPrice<<"\n";
          }
          else
          {
            std::cout<<"not found id:" << id << "\n";
          }
        }
        break;

      case 4://IDで削除
        {
          ItemId id;
          std::cout<<"Input remove id:";
          std::cin>>id;
          bool result=itemList.RemoveItemById( id );
          if( result )
          {
            std::cout<<"remove "<<id<<" is success!\n";
          }
          else
          {
            std::cout<<"remove "<<id<<" is failed\n";
          }

        }
        break;
      case 5:
        itemList.DisplaySortedItemListByPrice();
        std::cout<<"\n";
        break;
    }

    if( exit ){
      break;
    }
  }
  std::cout<<"item-manager is end\n";

  return 0;
}


