#include <cmath>
struct CollisionInfo {
	bool collision;
																  //### ###
	int x1; //distance between right side A and left side B		  //# * * #
																  //### ###
																  //     
																  //### ###
	int x2; //distance between left side A and right side B		  //* # # *
																  //### ###
																  //     
																  //### #*#
	int y1; //distance between bottom side A and top side B		  //# # # #
																  //#*# ###
																  //     
																  //#*# ###
	int y2; //distance between top side A and bottom side B		  //# # # #
																  //### #*#
	explicit operator bool() const {
		return collision;
	}
};
struct Square {
	int x, y, width, height;
};

CollisionInfo checkCollision(Square box1, /*static obj*/Square box2) {
	int x1 = box1.x + box1.width - box2.x;
	int x2 = box1.x - box2.x - box2.width;
	if (x1 < 0 || x2 > 0) {
		return { false };
	}

	int y1 = box1.y + box1.height - box2.y;
	int y2 = box1.y - box2.y - box2.height;
	if (y1 < 0 || y2 > 0) {
		return { false };
	}

	return { true, x1,x2,y1,y2 };
}
struct LeftTriangle {
	int x, y;
	int SIDE;
};

CollisionInfo checkCollision(Square box, /*static obj*/LeftTriangle tri) {
	if (box.y + box.height < tri.y) return { false };
	if (box.x > tri.x + tri.SIDE) return { false };

	int x1 = tri.x - box.x - box.width;
	if (x1 > 0) return { false };

	int y2 = tri.y + tri.SIDE - box.y;
	if (y2 < 0) return{ false };

	int Xdif = std::min(box.x - tri.x, 0);
	int topY = tri.y + Xdif;
	int y1 = topY - box.y;
	if (y1 > 0) return { false };
	int x2 = -y1;

	return{ true, x1,x2,y1,y2 };
}
struct RightTriangle {
	int x, y;
	int SIDE;
};
CollisionInfo checkCollision(Square box, /*static obj*/RightTriangle tri) {
	if (box.y + box.height < tri.y) return { false };
	if (box.x > tri.x + tri.SIDE) return { false };

	int x1 = tri.x - box.x - box.width;
	if (x1 > 0) return { false };

	int y2 = tri.y + tri.SIDE - box.y;
	if (y2 < 0) return{ false };

	int Xdif = std::min(tri.x - box.x,0);
	int topY = tri.y + Xdif;
	int y1 = topY - box.y;
	if (y1 > 0) return { false };
	int x2 = y1;

	return{ true, x1,x2,y1,y2 };
}


