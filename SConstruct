env = Environment()

var = Variables()
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
	),
	EnumVariable(
		"graphics", "target graphics engine.", "opengl",
		allowed_values = [ "opengl", "directx" ]
	)
)

env = Environment(variables = var, tools = [ "clang" ])
env.Append(
	CPPDEFINES = [
		"PLATFORM_" + env["platform"].upper(),
		"GRAPHICS_" + env["graphics"].upper()
	],
	CPPPATH = [ "#engine" ],
	CXXFLAGS = "-fcolor-diagnostics"
)

# profile
if env["build"] == "release":
	env.Append(CCFLAGS = "-O3")
elif env["build"] == "debug":
	env.Append(CCFLAGS = "-g", CPPDEFINES = [ "DEBUG" ])

if GetOption("help"):
	Help(var.GenerateHelpText(env))
	Exit()

env.SConscript(
	"engine/SConscript", exports = [ "env" ],
	variant_dir = "$build/engine", duplicate = False,
)
