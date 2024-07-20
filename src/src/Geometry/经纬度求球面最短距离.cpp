// lontitude 经度范围: $\pm\pi$, latitude 纬度范围: $\pm\pi/2$
LD sphereDis(LD lon1, LD lat1, LD lon2, LD lat2, LD R) {
	return R * acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2) + sin(lat1) * sin(lat2)); }