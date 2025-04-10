#pragma once
#include "core/base/error.h"
#include "function/render/debugdraw/debug_draw.h"
#include "function/render/debugdraw/debug_draw_manager.h"


namespace Toon
{

    class DebugDrawPrimitive : public DebugDraw
    {
    public:

        void draw(float delta_time) override;

        void initialize()  override;

        void clear()  override;
    public:
		void prepareVBO() {
			//1 创建一个vbo  *******还没有真正分配显存*********
			GLuint vbo = 0;
			GL_CALL(glGenBuffers(1, &vbo));

			//2 销毁一个vbo
			GL_CALL(glDeleteBuffers(1, &vbo));

			//3 创建n个vbo
			GLuint vboArr[] = { 0, 0, 0 };
			GL_CALL(glGenBuffers(3, vboArr));

			//4 销毁n个vbo
			GL_CALL(glDeleteBuffers(3, vboArr));
		}

		void prepare() {
			float vertices[] = {
				   -0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.0f,  0.5f, 0.0f
			};

			//1 生成一个vbo
			GLuint vbo = 0;
			GL_CALL(glGenBuffers(1, &vbo));

			//2 绑定当前vbo，到opengl状态机的当前vbo插槽上
			//GL_ARRAY_BUFFER:表示当前vbo这个插槽
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

			//3 向当前vbo传输数据，也是在开辟显存
			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		}

		void prepareSingleBuffer() {
			//1 准备顶点位置数据与颜色数据
			float positions[] = {
				   -0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.0f,  0.5f, 0.0f
			};
			float colors[] = {
			   1.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f,
			   0.0f,  0.0f, 1.0f
			};

			//2 为位置&颜色数据各自生成一个vbo
			GLuint posVbo = 0, colorVbo = 0;
			GL_CALL(glGenBuffers(1, &posVbo));
			GL_CALL(glGenBuffers(1, &colorVbo));

			//3 给两个分开的vbo各自填充数据
			//position填充数据
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

			//color填充数据
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
		}

		void prepareInterleavedBuffer() {
			float vertices[] = {
				   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
					0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
					0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
			};

			GLuint vbo = 0;
			GL_CALL(glGenBuffers(1, &vbo));

			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

		}
    private:
    };

}