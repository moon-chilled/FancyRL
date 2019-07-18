#ifndef BEING_H
#define BEING_H

typedef enum {
	Being_User,
	Being_Monster,
} BeingType;

typedef enum {
	BeingSpec_DefaultUser,
	BeingSpec_Orc,
	_BeingSpec_last,
} BeingSpecType;

typedef struct {
} UserBeing;

typedef struct {
} MonBeing;

typedef struct {
	char *name;
	u32 glyph;
	u32 fg, bg;
	u32 maxhp;
	u32 speed;
} BeingSpec;
typedef struct {
	// spec specifies default behaviour for a being.  However, those
	// attributes can change in a given instance so they are repeated
	BeingSpec spec;

	char *name;
	u32 glyph;
	u32 fg, bg;
	u32 hp, maxhp;
	u32 speed;
	i32 energy;
	u32 y, x;
} BeingBase;


typedef struct {
	BeingType type;
	BeingBase base;
	void *instance;
} Being;
typedef struct {
	BeingType type;
	BeingBase base;
	UserBeing *user;
} UBeing;
typedef struct {
	BeingType type;
	BeingBase base;
	MonBeing *mon;
} MBeing;

extern Being new_user(BeingSpecType spec);
extern Being new_mon(BeingSpecType spec);
extern UBeing user(Being b);
extern MBeing mon(Being b);
extern void delete_being(Being b);

extern BeingSpec being_specs[_BeingSpec_last];

#endif //BEING_H
