#include "item.h"
void updateItems(std::vector<PowerItem>& items, player& player,float dt)
{
	for (PowerItem& item : items)
	{
		item.y += 100.0f*dt;
		float inX = fabs(player.x - item.x);
		float inY = fabs(player.y - item.y);
		if (inX < item.collectRadius || inY < item.collectRadius)
		{
			if (inX != 0 && inY != 0)
			{
				item.x -= (item.x - player.x) / inX;
				item.y -= (item.y - player.y) / inY;
			}
			if (inX < 10 || inY < 10)
			{
				item.alive = false;
				player.power += item.value;
				if (player.power > player.maxPower) player.power = player.maxPower;
			}
		}

		if (item.x>672 || item.y > 990)//Àë¿ª´°¿ÚÅĞ¶¨ËÀÍö
		{
			item.alive = false;
		}
	}
	items.erase(std::remove_if(items.begin(), items.end(),
		[](PowerItem& it) { return !it.alive; }), items.end());
}
void drawItems(const std::vector<PowerItem>& items)
{
	for (const PowerItem& item : items)
	{
		if (item.alive == true)
		{
			putimage((int)item.x,(int)item.y, item.w,item.h,&item_white,194,2, NOTSRCERASE);//12/12
			putimage((int)item.x, (int)item.y, item.w, item.h, &item_, 194, 2, SRCINVERT);
		}
	}
}