#include <Artifax.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Artifax::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(Artifax::OrthographicCamera(-1.6, 1.6f, -0.9f, 0.9f))
	{
		m_VertexArray.reset(Artifax::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<Artifax::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Artifax::VertexBuffer::Create(vertices, sizeof(vertices)));
		Artifax::BufferLayout layout = {
			{Artifax::ShaderDataType::Float3, "a_Position"},
			{Artifax::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Artifax::IndexBuffer> indexBuffer;
		indexBuffer.reset(Artifax::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Artifax::VertexArray::Create());

		float squaredVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Artifax::VertexBuffer> squareVB;
		squareVB.reset(Artifax::VertexBuffer::Create(squaredVertices, sizeof(squaredVertices)));
		squareVB->SetLayout(
			{
				{Artifax::ShaderDataType::Float3, "a_Position"},
			}
		);
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Artifax::IndexBuffer> squareIB;
		squareIB.reset(Artifax::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
						
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
						
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}	
		)";

		m_Shader.reset(Artifax::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
						
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}	
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
						
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}	
		)";

		m_FlatColorShader.reset(Artifax::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}
private:
	std::shared_ptr<Artifax::Shader> m_Shader;
	std::shared_ptr<Artifax::VertexArray> m_VertexArray;

	std::shared_ptr<Artifax::Shader> m_FlatColorShader;
	std::shared_ptr<Artifax::VertexArray> m_SquareVA;

	Artifax::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
public:

	virtual void OnUpdate(Artifax::Timestep ts) override
	{
		if (Artifax::Input::IsKeyPressed(AX_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Artifax::Input::IsKeyPressed(AX_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Artifax::Input::IsKeyPressed(AX_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Artifax::Input::IsKeyPressed(AX_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Artifax::Input::IsKeyPressed(AX_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if(Artifax::Input::IsKeyPressed(AX_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		Artifax::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Artifax::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Artifax::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		Artifax::Renderer::Submit(m_FlatColorShader, m_SquareVA);
		Artifax::Renderer::Submit(m_Shader, m_VertexArray);


		Artifax::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(Artifax::Event& event) override
	{
	}
};

class Sandbox : public Artifax::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Artifax::Application* Artifax::CreateApplication()
{
	return new Sandbox();
}