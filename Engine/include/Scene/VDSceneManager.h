/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VDENGINE_SCENEMANAGER_H_
#define _VDENGINE_SCENEMANAGER_H_ 1
#include "VDScene.h"

/**
 *
 */
class FVDECLSPEC VDSceneManager {
  public:
	SceneManager();

	SceneManager(const SceneManager &scene);

	~SceneManager();

	/**
	 *
	 * @return
	 */
	Scene *getCurrentScene() const;

	/**
	 *
	 * @param scene
	 */
	void setCurrentScene(Scene *scene);

	/**
	 *
	 * @param index
	 * @param scene
	 */
	void setScene(int index, Scene *scene);

	/**
	 *
	 * @param index
	 * @return
	 */
	Scene *getScene(int index);

	/**
	 *
	 * @return
	 */
	Scene *getNextScene();

	/**
	 *
	 * @return
	 */
	Scene *getPreviousScene();

  private:
	std::vector<Scene *> scenes;
	std::vector<Scene *>::iterator current;
};

#endif
