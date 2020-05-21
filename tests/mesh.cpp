#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <memory>

#include "mesh.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(builderTest, testFlatWithoutColor) {
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

    auto layout = builder->build();

    ASSERT_THAT(
        layout.vertices,
        testing::ElementsAre(
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1)
        )
    );

    ASSERT_THAT(
        layout.normals,
        testing::ElementsAre(
            glm::vec3(0.5, 0.5, 0),
            glm::vec3(1, 0.5, 0)
        )
    );

    ASSERT_THAT(
        layout.tex_coords,
        testing::ElementsAre(
            glm::vec2(0, 0),
            glm::vec2(0.5, 0.5),
            glm::vec2(0, 0.5),
            glm::vec2(0.5, 0)
        )
    );

    ASSERT_THAT(
        layout.colors,
        testing::ElementsAre(
            glm::vec4(0, 0, 0, 1)
        )
    );

    ASSERT_EQ(layout.faces.size(), 2);

    ASSERT_THAT(layout.faces[0].vertices_indices, testing::ElementsAre(0, 1, 2));
    ASSERT_THAT(layout.faces[0].normals_indices, testing::ElementsAre(0, 1, 0));
    ASSERT_THAT(layout.faces[0].tex_coord_indices, testing::ElementsAre(0, 1, 2));
    ASSERT_THAT(layout.faces[0].color_indices, testing::ElementsAre(0, 0, 0));

    ASSERT_THAT(layout.faces[1].vertices_indices, testing::ElementsAre(2, 0, 0));
    ASSERT_THAT(layout.faces[1].normals_indices, testing::ElementsAre(0, 1, 1));
    ASSERT_THAT(layout.faces[1].tex_coord_indices, testing::ElementsAre(2, 3, 2));
    ASSERT_THAT(layout.faces[1].color_indices, testing::ElementsAre(0, 0, 0));
}

TEST(builderTest, testVertexCoordIndexValidation) {
    auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

    builder->push_vertex(glm::vec3(1, 0, 0));
    builder->push_vertex(glm::vec3(0, 1, 0));

    builder->push_normal(glm::vec3(0.5, 0.5, 0));
    builder->push_normal(glm::vec3(1, 0.5, 0));

    builder->push_tex_coord(glm::vec2(0, 0));
    builder->push_tex_coord(glm::vec2(0.5, 0.5));

    builder->push_triplet(mesh::Triplet(0, 0, 0));
    builder->push_triplet(mesh::Triplet(1, 1, 1));

    // Bad index: 20
    builder->push_triplet(mesh::Triplet(20, 0, 2));
    builder->push_triplet_face();

    EXPECT_THROW(builder->build(), mesh::ValidationException);
}

TEST(builderTest, testNormalIndexValidation) {
    auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

    builder->push_vertex(glm::vec3(1, 0, 0));
    builder->push_vertex(glm::vec3(0, 1, 0));

    builder->push_normal(glm::vec3(0.5, 0.5, 0));
    builder->push_normal(glm::vec3(1, 0.5, 0));

    builder->push_tex_coord(glm::vec2(0, 0));
    builder->push_tex_coord(glm::vec2(0.5, 0.5));

    builder->push_triplet(mesh::Triplet(0, 0, 0));
    builder->push_triplet(mesh::Triplet(1, 1, 1));

    // Bad index: 20
    builder->push_triplet(mesh::Triplet(2, 20, 2));
    builder->push_triplet_face();

    EXPECT_THROW(builder->build(), mesh::ValidationException);
}

TEST(builderTest, testFlatTexCoordIndexValidation) {
    auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

    builder->push_vertex(glm::vec3(1, 0, 0));
    builder->push_vertex(glm::vec3(0, 1, 0));

    builder->push_normal(glm::vec3(0.5, 0.5, 0));
    builder->push_normal(glm::vec3(1, 0.5, 0));

    builder->push_tex_coord(glm::vec2(0, 0));
    builder->push_tex_coord(glm::vec2(0.5, 0.5));

    builder->push_triplet(mesh::Triplet(0, 0, 0));
    builder->push_triplet(mesh::Triplet(1, 1, 1));

    // Bad index: 20
    builder->push_triplet(mesh::Triplet(2, 0, 20));
    builder->push_triplet_face();

    EXPECT_THROW(builder->build(), mesh::ValidationException);
}

TEST(builderTest, testTriangle) {
    auto builder = std::make_unique<mesh::MeshLayoutBuilder>();

    builder->push_triangle(
        mesh::Triangle {
            .vertices = {
                glm::vec3(1, 0, 0),
                glm::vec3(0, 1, 0),
                glm::vec3(0, 0, 1)
            },
            .normals = {
                glm::vec3(0, 0, 1),
                glm::vec3(0, 1, 0),
                glm::vec3(1, 0, 0)
            },
            .tex_coords = {
                glm::vec2(0, 0),
                glm::vec2(0, 1),
                glm::vec2(1, 0)
            },
        }
    );

    builder->push_vertex(glm::vec3(0, 1, 0));
    builder->push_vertex(glm::vec3(0, 0, 1));
    builder->push_tex_coord(glm::vec2(0, 1));

    builder->push_triangle(
        mesh::Triangle {
            .vertices = {
                glm::vec3(1, 0, 0),
                glm::vec3(1, 0, 0),
                glm::vec3(1, 0, 0)
            },
            .normals = {
                glm::vec3(0, 1, 0),
                glm::vec3(0, 1, 0),
                glm::vec3(0, 1, 0)
            },
            .tex_coords = {
                glm::vec2(1, 0),
                glm::vec2(1, 0),
                glm::vec2(1, 0)
            },
        }
    );

    auto layout = builder->build();

    ASSERT_THAT(
        layout.vertices,
        testing::ElementsAre(
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 0)
        )
    );

    ASSERT_THAT(
        layout.normals,
        testing::ElementsAre(
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 0)
        )
    );

    ASSERT_THAT(
        layout.tex_coords,
        testing::ElementsAre(
            glm::vec2(0, 0),
            glm::vec2(0, 1),
            glm::vec2(1, 0),
            glm::vec2(0, 1),
            glm::vec2(1, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 0)
        )
    );

    ASSERT_THAT(
        layout.colors,
        testing::ElementsAre(
            glm::vec4(0, 0, 0, 1)
        )
    );

    ASSERT_EQ(layout.faces.size(), 2);

    ASSERT_THAT(layout.faces[0].vertices_indices, testing::ElementsAre(0, 1, 2));
    ASSERT_THAT(layout.faces[0].normals_indices, testing::ElementsAre(0, 1, 2));
    ASSERT_THAT(layout.faces[0].tex_coord_indices, testing::ElementsAre(0, 1, 2));
    ASSERT_THAT(layout.faces[0].color_indices, testing::ElementsAre(0, 0, 0));

    ASSERT_THAT(layout.faces[1].vertices_indices, testing::ElementsAre(5, 6, 7));
    ASSERT_THAT(layout.faces[1].normals_indices, testing::ElementsAre(3, 4, 5));
    ASSERT_THAT(layout.faces[1].tex_coord_indices, testing::ElementsAre(4, 5, 6));
    ASSERT_THAT(layout.faces[1].color_indices, testing::ElementsAre(0, 0, 0));
}
