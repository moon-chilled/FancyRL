#include "being.h"

Being new_user(BeingSpecType spec) {
	UBeing ret = {0};
	ret.type = Being_User;
	ret.base.spec = being_specs[spec];

	ret.base.name = ret.base.spec.name;
	ret.base.glyph = ret.base.spec.glyph;
	ret.base.fg = ret.base.spec.fg;
	ret.base.bg = ret.base.spec.bg;
	ret.base.hp = ret.base.maxhp = ret.base.spec.maxhp;

	ret.user = alloc(sizeof(UserBeing));

	return *cast(Being*)&ret;
}
Being new_mon(BeingSpecType spec) {
	MBeing ret = {0};
	ret.type = Being_Monster;
	ret.base.spec = being_specs[spec];

	ret.base.name = ret.base.spec.name;
	ret.base.glyph = ret.base.spec.glyph;
	ret.base.fg = ret.base.spec.fg;
	ret.base.bg = ret.base.spec.bg;
	ret.base.hp = ret.base.maxhp = ret.base.spec.maxhp;

	ret.mon = alloc(sizeof(MonBeing));

	return *cast(Being*)&ret;
}
UBeing user(Being b) {
	assert (b.type = Being_User);
	return *cast(UBeing*)&b;
}
MBeing mon(Being b) {
	assert (b.type = Being_Monster);
	return *cast(MBeing*)&b;
}
void delete_being(Being b) {
	free(b.instance);
}

BeingSpec being_specs[_BeingSpec_last] = {
	[BeingSpec_DefaultUser] = {"user", '@', 0xffffff, 0x000000, 100},
	[BeingSpec_Orc] = {"bob", 'o', 0xff0000, 0x000000, 20},
};
