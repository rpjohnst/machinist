env = DefaultEnvironment()

var = Variables(".variables")
var.AddVariables(
	EnumVariable(
		"build", "set to debug for syms.", "debug",
		allowed_values = [ "debug", "release" ]
	),
	("platform", "target api.", env["PLATFORM"])
)

env = Environment(
	variables = var, tools = [],
	CPPDEFINES = { "PLATFORM": "$platform" },
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
