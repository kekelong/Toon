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
			//1 ����һ��vbo  *******��û�����������Դ�*********
			GLuint vbo = 0;
			GL_CALL(glGenBuffers(1, &vbo));

			//2 ����һ��vbo
			GL_CALL(glDeleteBuffers(1, &vbo));

			//3 ����n��vbo
			GLuint vboArr[] = { 0, 0, 0 };
			GL_CALL(glGenBuffers(3, vboArr));

			//4 ����n��vbo
			GL_CALL(glDeleteBuffers(3, vboArr));
		}

		void prepare() {
			float vertices[] = {
				   -0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.0f,  0.5f, 0.0f
			};

			//1 ����һ��vbo
			GLuint vbo = 0;
			GL_CALL(glGenBuffers(1, &vbo));

			//2 �󶨵�ǰvbo����opengl״̬���ĵ�ǰvbo�����
			//GL_ARRAY_BUFFER:��ʾ��ǰvbo������
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

			//3 ��ǰvbo�������ݣ�Ҳ���ڿ����Դ�
			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		}

		void prepareSingleBuffer() {
			//1 ׼������λ����������ɫ����
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

			//2 Ϊλ��&��ɫ���ݸ�������һ��vbo
			GLuint posVbo = 0, colorVbo = 0;
			GL_CALL(glGenBuffers(1, &posVbo));
			GL_CALL(glGenBuffers(1, &colorVbo));

			//3 �������ֿ���vbo�����������
			//position�������
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
			GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

			//color�������
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