namespace Pazu
{
	template <typename T>
	void World::AddObject(T *obj)
	{
        if constexpr (std::is_same_v<T, Sprite>)
        {
		    sprites.push_back(obj);
        }
	}

	template <typename T>
	void World::RemoveObject(T *obj)
	{
        if constexpr (std::is_same_v<T, Sprite>)
        {
		    sprites.erase(std::find(sprites.cbegin(), sprites.cend(), obj));
        }
	}

	template <typename T>
	void World::SetObject(T *obj)
    {
		if constexpr (std::is_same_v<T, Camera>)
		{
			this->activeCamera = obj;
			this->activeCamera->SetOrthoProjection(windowWidth, windowHeight);
		}
        else if constexpr (std::is_same_v<T, StateManager>)
        {
		    this->stateManager = obj;
        }
        else if constexpr (std::is_same_v<T, Input>)
        {
            this->input = obj;
        }
        else if constexpr (std::is_same_v<T, Time>)
        {
            this->time = obj;
        }
    }
}
