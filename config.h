/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
/* Default colors */
static const char def_gray1[]       = "#222222";
static const char def_gray2[]       = "#444444";
static const char def_gray3[]       = "#bbbbbb";
static const char def_gray4[]       = "#eeeeee";
static const char def_cyan[]        = "#005577";
static const char def1[]            = "#ffffff";
static const char def2[]            = "#ffffff";
static const char def3[]            = "#ffffff";
static const char def4[]            = "#ffffff";
static const char def5[]            = "#ffffff";
static const char def6[]            = "#ffffff";
/* Selenized black colors */
static const char sel_bg1[]         = "#252525";
static const char sel_dim0[]        = "#777777";
static const char sel_dim1[]        = "#a0a0a0";
static const char sel_fg0[]         = "#b9b9b9";
static const char sel_fg1[]         = "#dedede";
/* Catppuccin mocha colors */
static const char sel_cyan[]        = "#3fc5b7";
static const char cat_base[]        = "#1e1e2e";
static const char cat_text[]        = "#cdd6f4";
static const char cat_teal[]        = "#94e2d5";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { sel_fg0,  sel_bg1,    sel_bg1  },
	[SchemeCol1]  = { def1,     def_gray1,  def_gray2 },
	[SchemeCol2]  = { def2,     def_gray1,  def_gray2 },
	[SchemeCol3]  = { def3,     def_gray1,  def_gray2 },
	[SchemeCol4]  = { def4,     def_gray1,  def_gray2 },
	[SchemeCol5]  = { def5,     def_gray1,  def_gray2 },
	[SchemeCol6]  = { def6,     def_gray1,  def_gray2 },
	[SchemeSel]   = { sel_cyan, sel_bg1,    sel_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance	title	tags	mask	isfloating	monitor */
	{ "Gimp",	NULL,		NULL,	0,	1,	-1 },
	/* { "Firefox",	NULL,		NULL,	1 << 8,	0,	-1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY,	view,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		KEY,	toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,	tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,	{.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */
	/* { MOD, XK_a,     ACTION##stack, {.i = 0 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", def_gray1, "-nf", def_gray3, "-sb", def_cyan, "-sf", def_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

/* In keyboard order */

static const Key keys[] = {
	/* modifier			key		function	argument */
    	STACKKEYS(MODKEY,                          	focus)
	STACKKEYS(MODKEY|ShiftMask,                	push)
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,		{.v = (const char*[]){"slock", NULL} } },
	/* { MODKEY,			XK_grave,	spawn,		{.v = (const char*[]){ "dmenuunicode", NULL } } }, */
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_minus,	scratchpad_show,    {0} },
	{ MODKEY|ShiftMask,		XK_minus,	scratchpad_hide,    {0} },
	{ MODKEY,			XK_equal,	scratchpad_remove,  {0} },
	/* { MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("") },*/
	/* { MODKEY,			XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },*/
	/* { MODKEY|ShiftMask,		XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },*/

	{ MODKEY,			XK_Tab,		view,		{0} },
	/* { MODKEY|ShiftMask,		XK_Tab,		view,		{0} }, */
	{ MODKEY,			XK_q,		killclient,	{0} },
	/* { MODKEY,			XK_w,		spawn,		{.v = (const char*[]){"mullvad", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_w,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY,			XK_e,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY|ShiftMask,		XK_e,		quit,		{0} },
	/* { MODKEY,			XK_r,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_r,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{0} },
	/* { MODKEY|ShiftMask,		XK_t,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY,			XK_y,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_y,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY,			XK_u,		spawn,		{.v = (const char*[]){"gousermenu", NULL} } }, */
	/* { MODKEY|ShiftMask,		XK_u,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_o,		incnmaster,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,	{.i = -1 } },
	{ MODKEY,			XK_p,		spawn,		{.v = (const char*[]){"gopassmenu", NULL} } },
	{ MODKEY|ShiftMask,		XK_p,		spawn,		{.v = (const char*[]){"gousermenu", NULL} } },
	{ MODKEY,			XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY,			XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "repeat", NULL } } },
	{ MODKEY,			XK_backslash,		spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY|ShiftMask,		XK_backslash,		spawn,		{.v = (const char*[]){ "st", "-e", "ncmpcpp", NULL } } },

	{ MODKEY,			XK_a,		spawn,		SHCMD("get-bookmark | xargs chromium") },
	/* { MODKEY|ShiftMask,		XK_a,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_s,		togglebar,	{0} },
	{ MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("pkill -HUP gostatus && gostatus") },
	{ MODKEY,			XK_d,		spawn,		{.v=dmenucmd}},
	/* { MODKEY,			XK_d,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_d,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_f,		setlayout,	{.v = &layouts[1]} },
	/* { MODKEY|ShiftMask,		XK_f,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY,			XK_g,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_g,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_h,		setmfact,	{.f=-0.05}},
        /* j and k defined in STACKEYS */
	{ MODKEY,			XK_l,		setmfact,	{.f=+0.05}},
	/* { MODKEY,			XK_semicolon	spawn,		{.v = (const char*[]){"", NULL} } },*/
	/* { MODKEY|ShiftMask,		XK_semicolon,	spawn,		{.v = (const char*[]){"", NULL} } },*/
       	/* { MODKEY,			XK_apostrophe,	togglescratch,	{.ui = 1} }, */
	/* { MODKEY|ShiftMask,		XK_apostrophe,	spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_Return,	spawn,		{.v=termcmd}},
	/* { MODKEY|ShiftMask,		XK_Return,	spawn,		{.v = (const char*[]){"", NULL} } },*/

        { MODKEY,			XK_z,		spawn,		{.v = (const char*[]){"mullvad-browser-launcher", NULL} } },
	{ MODKEY|ShiftMask,		XK_z,		spawn,		{.v = (const char*[]){"tor-browser-launcher", NULL} } },
	{ MODKEY,			XK_x,		spawn,		SHCMD("get-bookmark | xargs firefox") },
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("get-bookmark | xargs firefox --private-window") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("get-bookmark | xargs -r surf") },
	{ MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("get-bookmark | xargs -r surf-incognito") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("xsel -bo | linkmenu") },
	{ MODKEY|ShiftMask,		XK_v,		spawn,		SHCMD("xsel -po | linkmenu") },
	{ MODKEY,			XK_b,		spawn,		SHCMD("get-bookmark | xargs -r xdotool type") },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("xclip -o | save-bookmark") },
	{ MODKEY,			XK_n,		spawn,		{.v = (const char*[]){"st", "-e", "newsraft", NULL} } },
	/* { MODKEY|ShiftMask,		XK_n,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_m,		setlayout,	{.v = &layouts[2]} },
	/* { MODKEY|ShiftMask,		XK_m,		spawn,		{.v = (const char*[]){"", NULL} } },*/
	{ MODKEY,			XK_comma,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_comma,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_period,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_period,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	{ 0,		XF86XK_AudioMute,		spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && pkill -SIGUSR1 gostatus") },
	{ 0,		XF86XK_AudioRaiseVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 4%+ && pkill -SIGUSR1 gostatus") },
	{ 0,		XF86XK_AudioLowerVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 4%- && pkill -SIGUSR1 gostatus") },
	{ 0,		XF86XK_AudioMicMute,		spawn,		{.v = (const char*[]){"wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL} } },
	{ 0,		XF86XK_MonBrightnessUp,		spawn,		{.v = (const char*[]){"brightnessctl", "set", "+5%", NULL} } },
	{ 0,		XF86XK_MonBrightnessDown,	spawn,		{.v = (const char*[]){"brightnessctl", "set", "5%-", NULL} } },
	/*{ 0,		XF86XK_Display,			spawn,		{.v = (const char*[]){"", NULL} } }, */
	{ 0,		XF86XK_WLAN,			spawn,		{.v = (const char*[]){"wifi", "toggle", NULL} } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdsblocks,    {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdsblocks,    {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdsblocks,    {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

