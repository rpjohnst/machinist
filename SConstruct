var = Variables(".variables")
var.AddVariables(
	EnumVariable(
		"build", "set to debug for syms.", "debug",
		allowed_values = [ "debug", "release" ]
	),
)

env = Environment(
	variables = var,
	tools = [ "default" ],
	
	LIBS = [ "X11", "GL" ]
)

if env["build"] == "debug":
	env.Append(CCFLAGS = " -g", CPPDEFINES = [ "DEBUG" ])

Help(var.GenerateHelpText(env))
var.Save(".variables", env)

if not GetOption("help"):
	env.SConscript(
		"SConscript", duplicate = False,
		exports = ["env"], variant_dir = env["build"],
	)
