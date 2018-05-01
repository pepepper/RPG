#include"savedata.h"
void levelup(int member) {
	switch(member){
		case 1:
			data.ouna.level++;
			data.ouna.battlestatus.ATK = data.ouna.battlestatus.ATK + 25;
			data.ouna.battlestatus.DEF = data.ouna.battlestatus.DEF + 25;
			data.ouna.battlestatus.MATK = data.ouna.battlestatus.MATK + 12;
			data.ouna.battlestatus.MDEF = data.ouna.battlestatus.MDEF + 12;
			data.ouna.battlestatus.SPD = data.ouna.battlestatus.SPD + 5;
			break;
		case 2:
			data.friend1.level++;
			data.friend1.battlestatus.ATK = data.friend1.battlestatus.ATK + 25;
			data.friend1.battlestatus.DEF = data.friend1.battlestatus.DEF + 25;
			data.friend1.battlestatus.MATK = data.friend1.battlestatus.MATK + 12;
			data.friend1.battlestatus.MDEF = data.friend1.battlestatus.MDEF + 12;
			data.friend1.battlestatus.SPD = data.friend1.battlestatus.SPD + 5;
			break;
		case 3:
			data.friend2.level++;
			data.friend2.battlestatus.ATK = data.friend2.battlestatus.ATK + 25;
			data.friend2.battlestatus.DEF = data.friend2.battlestatus.DEF + 25;
			data.friend2.battlestatus.MATK = data.friend2.battlestatus.MATK + 12;
			data.friend2.battlestatus.MDEF = data.friend2.battlestatus.MDEF + 12;
			data.friend2.battlestatus.SPD = data.friend2.battlestatus.SPD + 5;
			break;
		case 4:
			data.friend3.level++;
			data.friend3.battlestatus.ATK = data.friend3.battlestatus.ATK + 25;
			data.friend3.battlestatus.DEF = data.friend3.battlestatus.DEF + 25;
			data.friend3.battlestatus.MATK = data.friend3.battlestatus.MATK + 12;
			data.friend3.battlestatus.MDEF = data.friend3.battlestatus.MDEF + 12;
			data.friend3.battlestatus.SPD = data.friend3.battlestatus.SPD + 5;
			break;
	}
}