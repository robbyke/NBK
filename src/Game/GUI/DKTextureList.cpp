#include "../system.h"
#include <GL/gl.h>
#include <stdio.h>

#include "DKTextureLoader.h"
#include "DKTextureList.h"

using namespace std;

#ifdef WIN32
CDKTextureList::CDKTextureList(HWND hwnd)
#else
CDKTextureList::CDKTextureList()
#endif
{
	error=false;
#ifdef WIN32
	this->hwnd=hwnd;
#endif
}

CDKTextureList::~CDKTextureList()
{
	TexMapItr itr = textures.begin();
	for ( ; itr != textures.end(); itr++ )
	{
		delete itr->second;
	}
}

GLvoid CDKTextureList::add_texture(const char *name, const char *file, bool trans, GLint texture_filter, bool auto_transparent, GLubyte R, GLubyte G, GLubyte B)
{
	std::string texture_name = name;

	TEX_DATA *new_texture_info = new TEX_DATA();

	if (!file)
	{
		new_texture_info->file_name ='\0';
		textures[texture_name]=new_texture_info;
	}
	else
	{
		new_texture_info->set(file,trans,texture_filter,auto_transparent,R,G,B);
		textures[texture_name]=new_texture_info;
	}
}

GLvoid CDKTextureList::build_textures()
{
	CDKTextureLoader tl;

	TexMapItr iter = textures.begin();
	for (; iter != textures.end(); iter++)
	{
		TEX_DATA *tex_data = (*iter).second;

		if (tex_data->file_name.empty())
			continue;

		CDKTextureLoader::LOADER_RESULT lr = tl.build_texture(tex_data->file_name,tex_data->texture,tex_data->trans,tex_data->texture_filter,tex_data->auto_transparent,tex_data->R,tex_data->G,tex_data->B);

		if (!lr.result)
		{
			char err[512];
			sprintf(err,"Texture error: %s",tex_data->file_name.c_str());
#ifdef WIN32
			MessageBox( hwnd, err, "Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
#else
			printf("[ERROR|TEXTURE] %s\n", err);
#endif
		}
		else
		{
			tex_data->width=lr.texture_dimensions.x;
			tex_data->height=lr.texture_dimensions.y;
		}
	}
}

GLuint CDKTextureList::get_texture_by_name(const char *name)
{
	if (!name)
	{
#ifdef WIN32
		MessageBox(hwnd,"The texture by this name does not exist!","ERROR",MB_OK|MB_ICONERROR | MB_SETFOREGROUND);
#else
		printf("[ERROR|TEXTURE] The texture by this name does not exist!\n");
#endif
		return 0;
	}

	if (!textures[name])
	{
#ifdef WIN32
		char msg[255];
		sprintf(msg, "The texture by this name (%s) does not exist!", name);

		MessageBox(hwnd,msg,"ERROR",MB_OK|MB_ICONERROR | MB_SETFOREGROUND);
#else
		printf("[ERROR|TEXTURE] The texture by this name does not exist!\n");
#endif
		return 0;
	}
	else
	{
		return (*textures[name]).texture;
	}
}

CDKTextureList::TEX_DATA CDKTextureList::get_texture_data_by_name(const char *name)
{
	if (!name)
	{
#ifdef WIN32
		MessageBox(hwnd,"The texture by this name does not exist!","ERROR",MB_OK|MB_ICONERROR | MB_SETFOREGROUND);
#else
		printf("[ERROR|TEXTURE] The texture by this name does not exist!\n");
#endif
		return TEX_DATA();
	}

	if (!textures[name])
	{
#ifdef WIN32
		MessageBox(hwnd,"The texture by this name does not exist!","ERROR",MB_OK|MB_ICONERROR | MB_SETFOREGROUND);
#else
		printf("[ERROR|TEXTURE] The texture by this name does not exist!\n");
#endif
		return TEX_DATA();
	}	
	else
	{
		return *textures[name];
	}
}