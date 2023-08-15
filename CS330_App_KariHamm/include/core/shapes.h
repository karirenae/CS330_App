#pragma once

#include <rendering/types.h>

#include <numbers>
#include <tuple>
#include <vector>

struct Shapes {

	static inline void UpdateNormals(Vertex& p1, Vertex& p2, Vertex& p3)
	{
		glm::vec3 U = p2.Position - p1.Position;
		glm::vec3 V = p3.Position - p1.Position;

		auto normal = glm::cross(U, V);

		p1.Normal = normal;
		p2.Normal = normal;
		p3.Normal = normal;
	}

	static inline std::vector<Vertex> GetUnitCircleVertices(uint32_t sectorCount)
	{
		float sectorStep = 2.f * std::numbers::pi_v<float> / static_cast<float>(sectorCount);
		float sectorAngle;

		std::vector<Vertex> vertices{};

		for (auto i = 0; i <= sectorCount; i++)
		{
			sectorAngle = static_cast<float>(i) * sectorStep;
			vertices.push_back({
				.Position = {
					std::cos(sectorAngle),
					std::sin(sectorAngle),
					0
				}
				});
		}

		return vertices;
	}

	static inline std::vector<Vertex> cubeVertices
	{
		// Front Face
		{
			.Position = {-0.5f, 0.5f, 0.5f}, // 0
			.Color = {1.f, 0.f, 0.f}
		},
		{
			.Position = {-0.5f, -0.5f, 0.5f}, // 1
			.Color = {1.f, 0.f, 0.f}
		},
		{
			.Position = {0.5f, -0.5f, 0.5f}, // 2
			.Color = {1.f, 0.f, 0.f}
		},
		{
			.Position = {0.5f, 0.5f, 0.5f}, // 3
			.Color = {1.f, 0.f, 0.f}
		},
		// Right Side
		{
			.Position = {0.5f, 0.5f, 0.5f}, // 4
			.Color = {1.f, 1.f, 0.f}
		},
		{
			.Position = {0.5f, -0.5f, 0.5f}, // 5
			.Color = {1.f, 1.f, 0.f}
		},
		{
			.Position = {0.5f, -0.5f, -0.5f}, // 6
			.Color = {1.f, 1.f, 0.f}
		},
		{
			.Position = {0.5f, 0.5f, -0.5f}, // 7
			.Color = {1.f, 1.f, 0.f}
		},
		// Back Face
		{
			.Position = {0.5f, 0.5f, -0.5f}, // 8
			.Color = {0.f, 1.f, 0.f}
		},
		{
			.Position = {0.5f, -0.5f, -0.5f}, // 9
			.Color = {0.f, 1.f, 0.f}
		},
		{
			.Position = {-0.5f, -0.5f, -0.5f}, // 10
			.Color = {0.f, 1.f, 0.f}
		},
		{
			.Position = {-0.5f, 0.5f, -0.5f}, // 11
			.Color = {0.f, 1.f, 0.f}
		},
		// Left Face
		{
			.Position = {-0.5f, 0.5f, -0.5f}, // 12
			.Color = {0.f, 0.f, 1.f}
		},
		{
			.Position = {-0.5f, -0.5f, -0.5f}, // 13
			.Color = {0.f, 0.f, 1.f}
		},
		{
			.Position = {-0.5f, -0.5f, 0.5f}, // 14
			.Color = {0.f, 0.f, 1.f}
		},
		{
			.Position = {-0.5f, 0.5f, 0.5f}, // 15
			.Color = {0.f, 0.f, 1.f}
		},
		// Top Face
		{
			.Position = {-0.5f, 0.5f, -0.5f}, // 16
			.Color = {1.f, 1.f, 1.f}
		},
		{
			.Position = {-0.5f, 0.5f, 0.5f}, // 17
			.Color = {1.f, 1.f, 1.f}
		},
		{
			.Position = {0.5f, 0.5f, 0.5f}, // 18
			.Color = {1.f, 1.f, 1.f}
		},
		{
			.Position = {0.5f, 0.5f, -0.5f}, // 19
			.Color = {1.f, 1.f, 1.f}
		},
		// Bottom Face
		{
			.Position = {0.5f, -0.5f, 0.5f}, // 20
			.Color = {1.f, 0.f, 1.f}
		},
		{
			.Position = {0.5f, -0.5f, -0.5f}, // 21
			.Color = {1.f, 0.f, 1.f}
		},
		{
			.Position = {-0.5f, -0.5f, -0.5f}, // 22
			.Color = {1.f, 0.f, 1.f}
		},
		{
			.Position = {-0.5f, -0.5f, 0.5f}, // 23
			.Color = {1.f, 0.f, 1.f}
		}
	};

	static inline std::vector<uint32_t> cubeElements
	{
		0, 1, 3, 1, 2, 3, // Front Face	
		4, 5, 7, 5, 6, 7, // Right Face
		8, 9, 11, 9, 10, 11, // Back Face
		12, 13, 15, 13, 14, 15, // Left Face
		16, 17, 19, 17, 18, 19, // Top Face
		20, 21, 23, 21, 22, 23 // Bottom Face
	};


	static inline std::vector<Vertex> pyramidVertices
	{
		// Front Face
		{
			.Position = { 0.f, 0.5f, 0.f }, // 0 Top
			.Color = { 1.f, 1.f, 1.f }
		},
		{
			.Position = { -0.5f, -0.5f, 0.5f }, // 1
				.Color = { 1.f, 1.f, 0.f }
		},
		{
			.Position = {0.5f, -0.5f, 0.5f}, // 2
			.Color = {1.f, 0.f, 1.0f}
		},
		// Right Side
	{
		.Position = { 0.f, 0.5f, 0.f }, // 3 Top
		.Color = { 1.f, 1.f, 1.f }
	},
	{
		.Position = {0.5f, -0.5f, 0.5f}, // 4 (Same as 2)
		.Color = {1.f, 0.f, 1.0f}
	},
	{
		.Position = {0.5f, -0.5f, -0.5f}, // 5
		.Color = {0.f, 0.f, 1.f}
	},
		// Back Face
	{
		.Position = { 0.f, 0.5f, 0.f }, // 6 Top
		.Color = { 1.f, 1.f, 1.f }
	},
	{
		.Position = {0.5f, -0.5f, -0.5f}, // 7 (Same as 5)
		.Color = {0.f, 0.f, 1.f}
	},
	{
		.Position = {-0.5f, -0.5f, -0.5f}, // 8
		.Color = {0.f, 1.f, 1.f}
	},
		// Left Face
	{
		.Position = { 0.f, 0.5f, 0.f }, // 9 Top
		.Color = { 1.f, 1.f, 1.f }
	},
	{
		.Position = {-0.5f, -0.5f, -0.5f}, // 10 (Same as 8)
		.Color = {0.f, 1.f, 1.f}
	},
	{
		.Position = { -0.5f, -0.5f, 0.5f }, // 11
		.Color = { 1.f, 1.f, 0.f }
	},
		// Bottom Face
	{
		.Position = {0.5f, -0.5f, 0.5f}, // 12
		.Color = {1.f, 0.f, 1.f}
	},
	{
		.Position = {0.5f, -0.5f, -0.5f}, // 13
		.Color = {0.f, 0.f, 1.f}
	},
	{
		.Position = {-0.5f, -0.5f, -0.5f}, // 14
		.Color = {0.f, 1.f, 1.f}
	},
	{
		.Position = {-0.5f, -0.5f, 0.5f}, // 15
		.Color = {1.f, 1.f, 0.f}
	}
	};

	static inline std::vector<uint32_t> pyramidElements
	{
		0, 1, 2, // Front Face	
		3, 4, 5, // Right Face
		6, 7, 8, // Back Face
		9, 10, 11, // Left Face
		12, 13, 15, 13, 14, 15 // Bottom Face
	};

	static inline std::vector<Vertex> tableVertices
	{
		{
			.Position = {-1.f, 0.f, -1.f},
			.Color = {1.f, 0.f, 0.f}
		},
		{
			.Position = {-1.f, 0.f, 1.f},
			.Color = {0.f, 1.f, 0.f}
		},
		{
			.Position = {1.f, 0.f, -1.0f },
			.Color = {0.f, 1.f, 0.f}
		},
		{
			.Position = {1.f, 0.f, -1.0f},
			.Color = {1.f, 0.f, 0.f}
		},
		{
			.Position = {-1.f, 0.f, 1.0f},
			.Color = {0.f, 0.f, 1.f}
		},
		{
			.Position = {1.f, 0.f, 1.0f },
			.Color = {0.f, 1.f, 0.f}
		}
	};

	static inline std::vector<uint32_t> tableElements
	{
		0, 1, 2,
		3, 4, 5
	};

	static inline std::vector<Vertex> GetSphereVertices(float radius, float sectorCount, float stackCount)
	{
		std::vector<Vertex> vertices{};

		float PI = std::numbers::pi_v<float>;

		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
		float s, t;                                     // vertex texCoord

		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)


				// normalized vertex normal (nx, ny, nz)
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;

				// vertex tex coord (s, t) range between [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;

				vertices.push_back({
					.Position = { x, y, z},
					.Normal = { nx, ny, nz},
					.Uv = { s, t} });
			}
		}

		return vertices;
	};


	// Sphere elements
	static inline std::vector<uint32_t> GetSphereElements(float stackCount, float sectorCount)
	{
		std::vector<uint32_t> elements;
		std::vector<int> lineIndices;
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if (i != 0)
				{
					elements.push_back(k1);
					elements.push_back(k2);
					elements.push_back(k1 + 1);

				}

				// k1+1 => k2 => k2+1
				if (i != (stackCount - 1))
				{
					elements.push_back(k1 + 1);
					elements.push_back(k2);
					elements.push_back(k2 + 1);
				}

				// store indices for lines
				// vertical lines for all stacks, k1 => k2
				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}
			}
		}

		return elements;
	};
};