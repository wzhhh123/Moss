#pragma once


#ifdef MOSS_PLATFORM_WINDOWS

extern  Moss::Application*  Moss::CreateApplication();

int main(int argc, char** argv)
{

	Moss::Log::Init();
	MS_CORE_WARN("Initialized Log!");
	MS_CLIENT_INFO("hello!");

	auto app = Moss::CreateApplication();
	app->Run();
	delete app;
}


#endif