void AddToOrder(ORDERS_TYPE &orders, int id, Item &item, Diner &diner)
{

  ORDERS_TYPE::iterator o_itr = orders.begin();
  while (o_itr != orders.end())
  {
    if (o_itr->first.getID() == id)
    {
      o_itr->first.items.push_back(item);
      break;
    }
  }

  if (o_itr == orders.end())
  {
    Order odr(id);
    odr.items.push_back(items);
    orders[odr] = diner;
  }
}

BILLS_TYPE CalculateBills(const ORDERS_TYPE &orders)
{
  BILLS_TYPE bills;
  for (ORDERS_TYPE::iterator o_itr = orders.begin(); o_itr != orders.end(); o_itr++)
  {
    bills[o_itr->second] = 0;
    std::vector<Item> items = o_itr->first.getItems();
    for (int i = 0; i < items.size(); i++)
    {
      bills[o_itr->second] += items[i].getPrice();
    }
  }
  return bills;
}