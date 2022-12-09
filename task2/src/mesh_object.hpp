#pragma once

#include "game_object.hpp"
#include "mesh.hpp"

class MeshObject : public GameObject {
public:
    MeshObject(std::shared_ptr<Mesh> mesh) : mesh_(mesh) {} 
    virtual ~MeshObject() override = default;

    virtual void OnRender(GameWorld* world, const RenderView& render_view) override {
        Shader* shader = mesh_->material->GetShader();
        shader->LoadUniformMat4(GetModelMatrix(), "model");
        shader->LoadUniformMat4(render_view.view_matrix, "view");
        shader->LoadUniformMat4(render_view.proj_matrix, "proj");
        shader->LoadUniformFloat(render_view.time, "time");
        mesh_->material->LoadUniformsToShader();

        mesh_->Bind();
        mesh_->Draw();
    }

    void SetMesh(std::shared_ptr<Mesh> mesh) { mesh_ = mesh; }
    Mesh* GetMesh() const { return mesh_.get(); }

private:
    std::shared_ptr<Mesh> mesh_{nullptr};
};
