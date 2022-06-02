/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx        = 3;        /* border pixel of windows */
static const unsigned int gappx           = 8;        /* gaps between windows */
static const unsigned int snap            = 32;       /* snap pixel */
static const unsigned int systraypinning  = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;        /* systray spacing */
static const int systraypinningfailfirst  = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;        /* 0 means no systray */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const int horizpadbar              = 0;        /* horizontal padding for statusbar */
static const int vertpadbar               = 8;        /* vertical padding for statusbar */
static const int focusonwheel             = 0;
static const char *fonts[]                = { "JetBrainsMono Nerd Font:size=12", "Material Design Icons-Regular:size=10" };

static const char normbgcolor[]           = "#282a36";
static const char normbordercolor[]       = "#282a36";
static const char normfgcolor[]           = "#f8f8f2";
static const char selfgcolor[]            = "#ffb86c";
static const char selbordercolor[]        = "#ffb86c";
static const char selbgcolor[]            = "#282a36";
static const char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance                                   title       tags mask     isfloating   monitor */
	{ NULL,        "crx__pkooggnaalmfkidjmlhoelhdllpphaga",   NULL,       1,	        0,           1 }, // Outlook
	{ "Slack",     NULL,                                      NULL,       1 << 1,       0,           1 },
	{ "zoom",      NULL,                                      NULL,       1 << 2,       0,           1 },
	{ NULL,        "qalculate-gtk",                           NULL,       0,            1,           0 },
	{ "Kazam",     NULL,                                      NULL,       0,            1,           0 },
	{ "Signal",    NULL,                                      NULL,       1 << 8,       0,           2 },
	{ NULL,        "crx__hnpfjngllnobngcgfapefoaidbinmjnm",   NULL,       1 << 8,       0,           2 }, // Whats App
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* Layout per monitor */
/* Index of lpm equals to the monitor number */
/* Value of lpm equals to the layout number */
static const int lpm[] = {
	0, 2
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *roficmd[] = { "rofi", "-show", NULL };
static const char *windowcmd[] = { "rofi", "-show", "window", "-theme", "Dracula-window", NULL };
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
	/* modifier           key                         function        argument */
	{ MODKEY,             XK_p,                       spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,   XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,             XK_b,                       togglebar,      {0} },
	{ MODKEY,             XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_Tab,                     focusstack,     {.i = -1 } },
	{ MODKEY,             XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_minus,                   setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_equal,                   setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_Return,                  zoom,           {0} },
	{ MODKEY|ShiftMask,   XK_c,                       killclient,     {0} },
	{ MODKEY,             XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,   XK_m,                       spawn,	      SHCMD("sb-mic -t") },
	{ MODKEY,			  XK_c,                       spawn,	      SHCMD("sb-mic -t") }, // Microphone button on Keychron
	{ MODKEY,             XK_space,                   setlayout,      {0} },
	{ MODKEY,             XK_w,                       spawn,          {.v = windowcmd } },
	{ MODKEY|ShiftMask,   XK_space,                   togglefloating, {0} },
	{ MODKEY,             XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,                       tag,            {.ui = ~0 } },
	TAGKEYS(              XK_1,                                       0)
	TAGKEYS(              XK_2,                                       1)
	TAGKEYS(              XK_3,                                       2)
	TAGKEYS(              XK_4,                                       3)
	TAGKEYS(              XK_5,                                       4)
	TAGKEYS(              XK_6,                                       5)
	TAGKEYS(              XK_7,                                       6)
	TAGKEYS(              XK_8,                                       7)
	TAGKEYS(              XK_9,                                       8)
	{ MODKEY|ShiftMask,   XK_q,                       spawn,          SHCMD("off") },
	{ MODKEY,             XK_F1,                      focusnthmon,    {.i = 2 } },
	{ MODKEY,             XK_F2,                      focusnthmon,    {.i = 0 } },
	{ MODKEY,             XK_F3,                      focusnthmon,    {.i = 1 } },
	{ MODKEY,             XK_F5,                      quit,           {0} },
	{ MODKEY|ShiftMask,   XK_F1,                      tagnthmon,      {.i = 2 } },
	{ MODKEY|ShiftMask,   XK_F2,                      tagnthmon,      {.i = 0 } },
	{ MODKEY|ShiftMask,   XK_F3,                      tagnthmon,      {.i = 1 } },
	{ MODKEY,             XK_period,                  spawn,          SHCMD("rofi-emoji-picker") }, // Emoji picker
	{ MODKEY,             XK_s,                       spawn,          SHCMD("screenshot") }, // Creates a screenshot and copies it to the clipboard
	{ MODKEY|ShiftMask,   XK_s,                       spawn,          SHCMD("screenshot -select") }, // Creates a screenshot of a region and copies it to the clipboard
	{ MODKEY,             XK_Escape,                  spawn,          SHCMD("lock") },
	{ MODKEY|ShiftMask,   XK_Escape,                  spawn,          SHCMD("off") },
	{ MODKEY, 			  XK_z,                       spawn,          SHCMD("boomer") },
	{ 0,                  XF86XK_AudioPlay,           spawn,          SHCMD("playerctl play-pause") },
	{ 0,                  XF86XK_AudioRaiseVolume,    spawn,          SHCMD("sb-volume -i") },
	{ 0,                  XF86XK_AudioLowerVolume,    spawn,          SHCMD("sb-volume -d") },
	{ 0,                  XF86XK_AudioMute,           spawn,          SHCMD("sb-volume -t") },
	{ MODKEY,             XK_e,				          spawn,          SHCMD("calc") }, // Calculator button on Keychron
	{ 0,                  XF86XK_MonBrightnessUp,     spawn,          SHCMD("backlight --inc") },
	{ 0,                  XF86XK_MonBrightnessDown,   spawn,          SHCMD("backlight --dec") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        killclient,     {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

