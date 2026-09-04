#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <optional>

//商品ID
using ItemId = int;


//商品データ
class Item
{
public:

  Item(ItemId id, std::string name, int price)
    :mId(id),mName(std::move(name)),mPrice(price)
  {
  }
  
  ItemId GetItemId() const
  {
    return mId;
  }
  int GetPrice() const
  {
    return mPrice;
  }
  const std::string& GetName() const
  {
    return mName;
  }

private:
  ItemId mId;
  std::string mName;
  int mPrice;
};


//商品管理
class ItemManager
{
private:
  ItemId mNextItemId = 0;
  std::vector<Item> mItems;

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
    mItems.emplace_back( itemId, std::move(name), price );
    return itemId;
  }

  //IDから商品を検索する
  const Item *SearchItemById( ItemId id ) const
  {
    auto it = std::find_if(
      mItems.begin(),
      mItems.end(),
      [id](const Item& a)
      {
        return id == a.GetItemId();
      }
    );
    if( it != mItems.end() ){
      return &(*it);
    }
    return nullptr;
  }
  //IDを指定して商品を削除する
  bool RemoveItemById( ItemId id )
  {
    auto newEnd = std::remove_if(
      mItems.begin(),
      mItems.end(),
      [id]( const Item& a)
      {
        return id == a.GetItemId();
      }
    );
    if( newEnd == mItems.end() )
    {
      return false;
    }
    mItems.erase( newEnd, mItems.end() );
    return true;
  }

  //価格順に並び替えた商品のリストを取得する
  std::vector<const Item*> GetItemListSortedByPrice()const
  {
    std::vector<const Item*> list;
    for( const Item &item : mItems)
    {
        list.push_back( &item );
    }
    std::sort(
      list.begin(),
      list.end(),
      [](const Item *a, const Item *b)
      {
        return a->GetPrice() < b->GetPrice();
      }
    );
    return list;
  }

  const std::vector<Item>& GetItems() const
  {
    return mItems;
  }

  std::optional<int> GetPriceById( ItemId id ) const
  {
    auto it = std::find_if(
      mItems.begin(),
      mItems.end(),
      [id](const Item& item)
      {
        return ( item.GetItemId() == id );
      }
    );

    if( it != mItems.end())
    {
        return it->GetPrice();
    }
    return std::nullopt;
  }
};


  


int main()
{
  enum class MenuCommand{
    End = 0,
    Add = 1,
    DisplayList = 2,
    Search = 3,
    Remove = 4,
    DisplaySorted = 5,
    DisplayPrice = 6,
  };
  
  std::cout<<"hello item-manager"<<'\n';


  ItemManager itemManager;
  itemManager.AddItem("apple",100);
  itemManager.AddItem("grape", 150);
  itemManager.AddItem("banana", 80);

  while(1){
    std::cout<<"\n";
    std::cout<<"--Menu--\n";
    std::cout<<" 1:add item\n";
    std::cout<<" 2:display list\n";
    std::cout<<" 3:search by id\n";
    std::cout<<" 4:remove by id\n";
    std::cout<<" 5:display sorted list by price\n";
    std::cout<<" 6:display price by id\n";
    std::cout<<" 0:End\n\n";
    std::cout<<" command? ";

    int input = 0;
    std::cin>>input;
    const MenuCommand menu = static_cast<MenuCommand>(input);

    bool exit = false;
    switch(menu)
    {
      default://不正な値
        std::cout<<"illegal command no:"<<input<<'\n';
        break;

      case MenuCommand::End://終了
        exit = true;
        break;

      case MenuCommand::Add://商品追加
        {
          std::cout<<"name?";
          std::string name;
          std::cin>>name;
          std::cout<<"price?";
          int price = 0;
          std::cin>>price;
          ItemId id = itemManager.AddItem( name, price );
          std::cout<<"item add id:" << id<<"\n";
        }
        break;

      case MenuCommand::DisplayList://リスト表示
        {
          const std::vector<Item> &items = itemManager.GetItems();
          for( const Item &item : items)
          {
            std::cout<<"Id:"<<item.GetItemId() << " name:" << item.GetName() << " price:"<<item.GetPrice()<<"\n";
          }
        }
        std::cout<<"\n";
        break;

      case MenuCommand::Search://ID検索
        {
          ItemId id;
          std::cout<<"Input search id:";
          std::cin>>id;
          const Item *item = itemManager.SearchItemById( id );
          if( item != nullptr)
          {
            std::cout<<"find!\n";
            std::cout<<"id:"<<id<<" "<<item->GetName() <<" "<<item->GetPrice()<<"\n";
          }
          else
          {
            std::cout<<"not found id:" << id << "\n";
          }
        }
        break;

      case MenuCommand::Remove://IDで削除
        {
          ItemId id;
          std::cout<<"Input remove id:";
          std::cin>>id;
          bool result = itemManager.RemoveItemById( id );
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

      case MenuCommand::DisplaySorted://価格順の商品リストを表示する
        {
          std::vector<const Item*> items = itemManager.GetItemListSortedByPrice();
          for( const Item *item : items )
          {
             std::cout<<"Id "<<item->GetItemId()<<" "<<item->GetName()<<" "<<item->GetPrice()<<"\n";
          }

        }
        std::cout<<"\n";
        break;

      case MenuCommand::DisplayPrice://IDを指定して価格を取得し表示する
        {
          ItemId id;
          std::cout<<"Input display price id:";
          std::cin>>id;
          std::optional<int> price = itemManager.GetPriceById(id);
          if(price)
          {
            std::cout<<"Id:"<<id<<" price:"<< price.value() <<"\n";
          }
          else
          {
            std::cout<<"Not found id:"<<id<<"\n";
          }
        }
        break;
    }

    if( exit ){
      break;
    }
  }
  std::cout<<"item-manager is end\n";

  return 0;
}


