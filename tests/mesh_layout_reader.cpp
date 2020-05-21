#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <memory>

#include "mesh.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

static std::shared_ptr<mesh::MeshLayout> mesh_layout() {
    auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

    builder->push_vertex(glm::vec3(1, 0, 0));
    builder->push_vertex(glm::vec3(0, 1, 0));
    builder->push_vertex(glm::vec3(0, 0, 1));

    builder->push_normal(glm::vec3(0.5, 0.5, 0));
    builder->push_normal(glm::vec3(1, 0.5, 0));

    builder->push_tex_coord(glm::vec2(0, 0));
    builder->push_tex_coord(glm::vec2(0.5, 0.5));
    builder->push_tex_coord(glm::vec2(0, 0.5));
    builder->push_tex_coord(glm::vec2(0.5, 0));

    builder->push_triplet(mesh::Triplet(0, 0, 0));
    builder->push_triplet(mesh::Triplet(1, 1, 1));
    builder->push_triplet(mesh::Triplet(2, 0, 2));
    builder->push_triplet_face();

    builder->push_triplet(mesh::Triplet(2, 0, 2));
    builder->push_triplet(mesh::Triplet(0, 1, 3));
    builder->push_triplet(mesh::Triplet(0, 1, 2));
    builder->push_triplet_face();

    builder->push_triangle(
        mesh::Triangle(
            {
                glm::vec3(1, 0, 0),
                glm::vec3(1, 0, 0),
                glm::vec3(1, 0, 0)
            },
            {
                glm::vec3(0, 1, 0),
                glm::vec3(0, 1, 0),
                glm::vec3(0, 1, 0)
            },
            {
                glm::vec2(1, 0),
                glm::vec2(1, 0),
                glm::vec2(1, 0)
            }
        )
    );

    builder->push_polygon(
        mesh::Polygon(
            {
                glm::vec3(1, 0, 1),
                glm::vec3(0, 1, 0),
                glm::vec3(0, 0, 1),
                glm::vec3(0, 1, 0)
            },
            {
                glm::vec3(1, 0, 0),
                glm::vec3(1, 0, 1),
                glm::vec3(0, 1, 0),
                glm::vec3(0, 1, 1)
            },
            {
                glm::vec2(1, 0),
                glm::vec2(1, 1),
                glm::vec2(1, 0),
                glm::vec2(1, 1)
            }
        )
    );

    return builder->build();
}

TEST(meshLayoutTest, basicAccessorsTest) {
    auto layout = mesh_layout();
    auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
    auto reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

    ASSERT_THAT(
        reader->vertices(),
        testing::ElementsAre(
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1),

            // Triangle
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 0),

            // Polygon
            glm::vec3(1, 0, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 0)
        )
    );

    ASSERT_THAT(
        reader->normals(),
        testing::ElementsAre(
            glm::vec3(0.5, 0.5, 0),
            glm::vec3(1, 0.5, 0),

            // Triangle
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 0),

            // Polygon
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 1)
        )
    );

    ASSERT_THAT(
        reader->tex_coords(),
        testing::ElementsAre(
            glm::vec2(0, 0),
            glm::vec2(0.5, 0.5),
            glm::vec2(0, 0.5),
            glm::vec2(0.5, 0),

            // Triangle
            glm::vec2(1, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 0),

            // Polygon
            glm::vec2(1, 0),
            glm::vec2(1, 1),
            glm::vec2(1, 0),
            glm::vec2(1, 1)
        )
    );
}

TEST(meshLayoutTest, tripletsTest) {
    auto layout = mesh_layout();
    auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
    auto reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

    ASSERT_THAT(
        reader->triplets(),
        testing::ElementsAre(
            mesh::Triplet(0, 0, 0),
            mesh::Triplet(1, 1, 1),
            mesh::Triplet(2, 0, 2),
            mesh::Triplet(2, 0, 2),
            mesh::Triplet(0, 1, 3),
            mesh::Triplet(0, 1, 2),

            // Triangle
            mesh::Triplet(3, 2, 4),
            mesh::Triplet(4, 3, 5),
            mesh::Triplet(5, 4, 6),

            // Polygon
            mesh::Triplet(6, 5, 7),
            mesh::Triplet(7, 6, 8),
            mesh::Triplet(8, 7, 9),
            mesh::Triplet(9, 8, 10)
        )
    );
}

TEST(meshLayoutTest, trianglesTest) {
    auto layout = mesh_layout();
    auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
    auto reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

    ASSERT_THAT(
        reader->triangles(),
        testing::ElementsAre(
            // Triplets
            mesh::Triangle(
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 0, 1)
                },
                {
                    glm::vec3(0.5, 0.5, 0),
                    glm::vec3(1, 0.5, 0),
                    glm::vec3(0.5, 0.5, 0)
                },
                {
                    glm::vec2(0, 0),
                    glm::vec2(0.5, 0.5),
                    glm::vec2(0, 0.5)
                }
            ),

            mesh::Triangle(
                {
                    glm::vec3(0, 0, 1),
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0)
                },
                {
                    glm::vec3(0.5, 0.5, 0),
                    glm::vec3(1, 0.5, 0),
                    glm::vec3(1, 0.5, 0)
                },
                {
                    glm::vec2(0, 0.5),
                    glm::vec2(0.5, 0),
                    glm::vec2(0, 0.5)
                }
            ),

            // Triangle
            mesh::Triangle(
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0)
                },
                {
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 0)
                },
                {
                    glm::vec2(1, 0),
                    glm::vec2(1, 0),
                    glm::vec2(1, 0)
                }
            ),

            // Polygon
            mesh::Triangle(
                {
                    glm::vec3(1, 0, 1),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 0, 1),
                },
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 1),
                    glm::vec3(0, 1, 0),
                },
                {
                    glm::vec2(1, 0),
                    glm::vec2(1, 1),
                    glm::vec2(1, 0),
                }
            ),

            mesh::Triangle(
                {
                    glm::vec3(1, 0, 1),
                    glm::vec3(0, 0, 1),
                    glm::vec3(0, 1, 0)
                },
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 1)
                },
                {
                    glm::vec2(1, 0),
                    glm::vec2(1, 0),
                    glm::vec2(1, 1)
                }
            )
        )
    );
}

TEST(meshLayoutTest, polygonsTest) {
    auto layout = mesh_layout();
    auto triangulation_strategy = std::make_shared<mesh::DummyTriangulationStrategy>();
    auto reader = std::make_unique<mesh::MeshLayoutReader>(layout, triangulation_strategy);

    ASSERT_THAT(
        reader->polygons(),
        testing::ElementsAre(
            // Triplets
            mesh::Polygon(
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 0, 1)
                },
                {
                    glm::vec3(0.5, 0.5, 0),
                    glm::vec3(1, 0.5, 0),
                    glm::vec3(0.5, 0.5, 0)
                },
                {
                    glm::vec2(0, 0),
                    glm::vec2(0.5, 0.5),
                    glm::vec2(0, 0.5)
                }
            ),

            mesh::Polygon(
                {
                    glm::vec3(0, 0, 1),
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0)
                },
                {
                    glm::vec3(0.5, 0.5, 0),
                    glm::vec3(1, 0.5, 0),
                    glm::vec3(1, 0.5, 0)
                },
                {
                    glm::vec2(0, 0.5),
                    glm::vec2(0.5, 0),
                    glm::vec2(0, 0.5)
                }
            ),

            // Triangle
            mesh::Polygon(
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 0)
                },
                {
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 0)
                },
                {
                    glm::vec2(1, 0),
                    glm::vec2(1, 0),
                    glm::vec2(1, 0)
                }
            ),

            // Polygon
            mesh::Polygon(
                {
                    glm::vec3(1, 0, 1),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 0, 1),
                    glm::vec3(0, 1, 0)
                },
                {
                    glm::vec3(1, 0, 0),
                    glm::vec3(1, 0, 1),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, 1, 1)
                },
                {
                    glm::vec2(1, 0),
                    glm::vec2(1, 1),
                    glm::vec2(1, 0),
                    glm::vec2(1, 1)
                }
            )
        )
    );
}
