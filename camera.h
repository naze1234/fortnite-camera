namespace camera
{
		fn::fvector location;
		fn::fvector rotation;
		float fov;
}

void update_camera()
{
		uintptr_t view_matrix_0 = read<uintptr_t>(fn::pointers::local_player + 0xc8); //it's better to cache this
		uintptr_t view_matrix_1 = read<uintptr_t>(view_matrix_0 + 0x8); //it's better to cache this
		uintptr_t ptr_location = read<uintptr_t>(fn::pointers::uworld + 0x100); //it's better to cache this

		camera::location = read<fn::fvector>(ptr_location);

		double pitch = asin(read<double>(view_matrix_1 + 0xae0)) * (180.0 / M_PI);
		double raw_yaw_c = read<double>(view_matrix_1 + 0x7b0);
		double raw_yaw_s = read<double>(view_matrix_1 + 0x790);

		double yaw = atan2(raw_yaw_s, raw_yaw_c) * (180.0 / M_PI);
		yaw *= -1;

		camera::rotation.x = pitch;
		camera::rotation.y = yaw;
		camera::rotation.z = 0;

		camera::fov = read_virtual<float>(fn::pointers::camera_fov + 0x4CC);
}
