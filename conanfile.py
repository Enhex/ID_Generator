import os

from conans import ConanFile, tools


class IdgeneratorConan(ConanFile):
	name = "ID_Generator"
	version = "master"
	license = "MIT"
	author = "<Put your name here> <And your email here>"
	url = "<Package recipe repository url here, for issues about the package>"
	description = "<Description of Idgenerator here>"
	topics = ("<Put some tag here>", "<here>", "<and here>")
	no_copy_source = True
	# No settings/options are necessary, this is header only
	exports_sources = "src/*"

	def package(self):
		self.copy("*.h", dst="include", src="src")
