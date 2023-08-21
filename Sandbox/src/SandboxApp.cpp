#include <Artifax.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Artifax::Layer
{
private:
	Artifax::Ref<Artifax::Shader> m_Shader;
	Artifax::Ref<Artifax::VertexArray> m_VertexArray;

	Artifax::Ref<Artifax::Shader> m_FlatColorShader, m_TextureShader;
	Artifax::Ref<Artifax::VertexArray> m_SquareVA;

	Artifax::Ref<Artifax::Texture2D> m_Texture;

	Artifax::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.f;

	glm::vec3 m_SquarePosition = glm::vec3(0.0f);
	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(Artifax::OrthographicCamera(-1.6, 1.6f, -0.9f, 0.9f))
	{
		AX_PROFILE_FUNCTION();

		m_VertexArray.reset(Artifax::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		Artifax::Ref<Artifax::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Artifax::VertexBuffer::Create(vertices, sizeof(vertices)));
		Artifax::BufferLayout layout = {
			{Artifax::ShaderDataType::Float3, "a_Position"},
			{Artifax::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Artifax::Ref<Artifax::IndexBuffer> indexBuffer;
		indexBuffer.reset(Artifax::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Artifax::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};
		Artifax::Ref<Artifax::VertexBuffer> squareVB;
		squareVB.reset(Artifax::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{Artifax::ShaderDataType::Float3, "a_Position"},
				{Artifax::ShaderDataType::Float2, "a_TexCoord"},
			}
		);
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Artifax::Ref<Artifax::IndexBuffer> squareIB;
		squareIB.reset(Artifax::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
						
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
						
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
						
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}	
		)";

		m_FlatColorShader.reset(Artifax::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;
						
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
						
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}	
		)";

		m_TextureShader.reset(Artifax::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Artifax::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}
public:

	virtual void OnUpdate(Artifax::Timestep ts) override
	{
		AX_PROFILE_FUNCTION();

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

		if (Artifax::Input::IsKeyPressed(AX_KEY_LEFT))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (Artifax::Input::IsKeyPressed(AX_KEY_RIGHT))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (Artifax::Input::IsKeyPressed(AX_KEY_UP))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (Artifax::Input::IsKeyPressed(AX_KEY_DOWN))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;


		Artifax::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Artifax::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation); 

		Artifax::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Artifax::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		m_Texture->Bind();
		Artifax::Renderer::Submit(m_TextureShader, m_SquareVA, squareTransform);

		//Artifax::Renderer::Submit(m_FlatColorShader, m_SquareVA, squareTransform);
		//Artifax::Renderer::Submit(m_Shader, m_VertexArray);


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