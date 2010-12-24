env = DefaultEnvironment()

var = Variables([ ".variables" ])
var.AddVariables(
	EnumVariable(
		"build", "set to debug for syms.", "debug",
		allowed_values = [ "debug", "release" ]
	),
	EnumVariable(
		"platform", "target api.", {
			"win32": "win32",
			"posix": "xlib"
		}[env["PLATFORM"]],
		allowed_values = [ "win32", "xlib" ]
	)
)

env = Environment(variables = var, tools = [ "clang" ])
env.Append(
	CPPDEFINES = [ "PLATFORM_" + env["platform"].upper() ],
	CPPPATH = [ "#engine" ]
)

# profile
if env["build"] == "release":
	env.Append(CCFLAGS = " -O3")
elif env["build"] == "debug":
	env.Append(CCFLAGS = " -g", CPPDEFINES = [ "DEBUG" ])

Help(var.GenerateHelpText(env))
var.Save(".variables", env)

if not GetOption("help"):
	env.SConscript(
		"engine/SConscript", duplicate = False,
		exports = [ "env" ], variant_dir = "$build/engine",
	)
