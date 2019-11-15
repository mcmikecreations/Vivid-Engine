namespace vivid_core
{
	namespace app
	{
		class application {
		public:
			int run();
		private:
			int initVulkan();
			int mainLoop();
			int cleanup();
		};
	}
}