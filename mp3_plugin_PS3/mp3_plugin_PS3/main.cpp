



#undef vector // disable annoying math vector from sdk

#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <cell/fs/cell_fs_errno.h>
#include <cell/fs/cell_fs_file_api.h>
#include <sysutil/sysutil_userinfo.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_msgdialog.h>
#include <sys/paths.h>
#include <sys/socket.h>
#include <sys/random_number.h>
#include <sysutil/sysutil_sysparam.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys\dbg.h>
#include <ppu_asm_intrinsics.h>
#include <ppu_intrinsics.h>
#include <cell/error.h>
#include <cell/cell_fs.h>
#include <cell/sysmodule.h>
#include <cellstatus.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fastmath.h>
#include <math.h>
#include <ctype.h>
#include <hash_map>
#include <hash_set>
#include <map>
#include <new>
#include <vector>
#include <typeinfo>
#include <pthread.h>
#include <time.h>
#include <locale.h>
#include <np.h>
#include <net\if_dl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>
#include <netex/libnetctl.h>
#include <arpa/inet.h>


#include "enums.h"
#include "utils.h"
#include "natives.h"
#include "nativeMemory.h"
#include "script.h"




SYS_MODULE_INFO(mp3_plugin_PS3, 0, 1, 1);
SYS_MODULE_START(MODULE_START);
SYS_MODULE_STOP(MODULE_STOP);
SYS_MODULE_EXIT(MODULE_STOP);




/*
credits
https://github.com/UnknownModder/mp3-plugin-sdk
unknownmodder
jedijosh920
dirk
therouletteboi
*/

void(*ORG_NATIVE_GET_PLAYER_ID)(NativeContext*);







#define MAX_PAINKILLERS 9
#define MAX_AMMO 25000

void scriptMain()
{
	if (PLAYER::DOES_MAIN_PLAYER_EXIST())
	{
		Player player = PLAYER::GET_PLAYER_ID();
		Ped playerPed = PLAYER::GET_PLAYER_PED(player);

		PLAYER::SET_PLAYER_INVINCIBLE(player, true);

		int num = PLAYER::GET_PAYNEKILLER_AMT();
		if (num < MAX_PAINKILLERS)
		{
			PLAYER::SET_PAYNEKILLER_AMT(MAX_PAINKILLERS);
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LEFT) && PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RDOWN))
		{
			if (!WEAPON::HAS_PED_GOT_WEAPON(playerPed, WEAPON_SMG_MP5))
				WEAPON::GIVE_WEAPON_TO_PED(playerPed, WEAPON_SMG_MP5, MAX_AMMO, true);
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RIGHT) && PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RDOWN))
		{
			const int ARR_SIZE = 256;

			Ped peds[ARR_SIZE];
			int count = worldGetAllPeds(peds, ARR_SIZE);

			for (int i = 0; i < count; i++)
			{
				if (peds[i] != playerPed)
				{
					Vector3 coords = PED::GET_PED_COORDS(peds[i]);
					FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, EXP_TAG_MOLOTOV, 1.0f, true, false, 1.0f);
				}
			}
		}
	}
}


void MY_NATIVE_GET_PLAYER_ID(NativeContext *cxt)
{
	scriptMain();
	ORG_NATIVE_GET_PLAYER_ID(cxt);
}





extern "C" int MODULE_START(void)
{
	native_table_address = 0x1D96D00;
	native_table_modulator = native_table_address + 0x4;
	g_Natives = (unsigned int*)native_table_address;


	nativeHook(0x1CC648EA, (unsigned int)MY_NATIVE_GET_PLAYER_ID);


    return 0;
}

extern "C" int MODULE_STOP(void)
{

	return 0;
}