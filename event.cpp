#include "savedata.h"
#include "inventory.h"
#include "event.h"
//0 money+-
//1 item(0)/head(1)/body(2)/arm(3)/foot(4)/weapon(5)+-
//2 HP(0)/MP(1)+-
//3 eventflag
//4 friend+-
//5 talk
MAPEVENT mapeventhairetu[2048] = {0};
void eventselect(MAPEVENT mapevent){
	int eventnum=0;
	while(mapevent.object[eventnum]){
		eventnum++;
	}
	for(int i = 0;i=eventnum;i++){
		switch(mapevent.object[i]){
			case 0:
				data.money+=mapevent.amount[i];
				break;
			case 1:
				addinventory(mapevent.type[i],mapevent.type2[i],mapevent.amount[i]);
				break;
			case 2:
				switch(mapevent.type[i]){
					case 0:
						data.ouna.battlestatus.HP+=mapevent.amount[i];
						break;
					case 1:
						data.ouna.battlestatus.MP+=mapevent.amount[i];
						break;
					case 2:
						data.friend1.battlestatus.HP+=mapevent.amount[i];
						break;
					case 3:
						data.friend1.battlestatus.MP+=mapevent.amount[i];
						break;
					case 4:
						data.friend2.battlestatus.HP+=mapevent.amount[i];
						break;
					case 5:
						data.friend2.battlestatus.MP+=mapevent.amount[i];
						break;
					case 6:
						data.friend3.battlestatus.HP+=mapevent.amount[i];
						break;
					case 7:
						data.friend3.battlestatus.MP+=mapevent.amount[i];
						break;
				}
				break;
			case 3:
				data.eventflag[mapevent.type[i]]=mapevent.amount[i];
				break;
			case 4:
				if(data.friend1.level=0)data.friend1=mobs[mapevent.amount[i]].mobstat;
				else if(data.friend2.level=0)data.friend2=mobs[mapevent.amount[i]].mobstat;
				else if(data.friend3.level=0)data.friend3=mobs[mapevent.amount[i]].mobstat;
				break;
		}
	}
}

void MapEvent(int mapeventnum){
	eventselect(mapeventhairetu[mapeventnum-2]);
}