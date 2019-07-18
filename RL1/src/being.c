#include "fancy.h"
#include "being.h"

static BeingBase base_from_spectype(BeingSpecType spec) {
	BeingBase ret = {0};

	ret.spec = being_specs[spec];

	ret.name = ret.spec.name;
	ret.glyph = ret.spec.glyph;
	ret.fg = ret.spec.fg;
	ret.bg = ret.spec.bg;
	ret.speed = ret.spec.speed;
	ret.hp = ret.maxhp = ret.spec.maxhp;

	return ret;
}

Being new_user(BeingSpecType spec) {
	UBeing ret = {0};
	ret.type = Being_User;
	ret.base = base_from_spectype(spec);

	ret.user = new(UserBeing);

	return *cast(Being*)&ret;
}
Being new_mon(BeingSpecType spec) {
	MBeing ret = {0};
	ret.type = Being_Monster;
	ret.base = base_from_spectype(spec);

	ret.mon = new(MonBeing);

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
	[BeingSpec_DefaultUser] = {"user", '@', 0x000000, 0xffffff, 100, 10},
	[BeingSpec_Orc] = {"bob", 'o', 0xff0000, 0x000000, 20, 8},
};
