#include "ItemClass.h"
#include "TBdefine.h"
#include <string.h>

ItemClass* ItemPtr = new ItemClass[ITEMNUM];

void InitItems(void) {
	strcpy_s((ItemPtr + 0)->name, "��Ȑ�");
	strcpy_s((ItemPtr + 0)->description, "��ȗ͂��󂯂Đk���Ă���B ���؂������ɂ͎育��Ȍ`�B");
}