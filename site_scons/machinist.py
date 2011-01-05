def Objects(env, sources):
	objects = []
	for source in sources:
		objects.extend(env.Object(source))
	return objects
