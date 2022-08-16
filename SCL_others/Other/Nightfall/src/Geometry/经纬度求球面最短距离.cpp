// lontitude 经度范围: $\pm\pi$, latitude 纬度范围: $\pm\pi/2$
double sphereDis(double lon1, double lat1, double lon2, double lat2, double R) {
	return R * acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2) + sin(lat1) * sin(lat2)); }