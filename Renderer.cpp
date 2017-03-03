#include "Renderer.h"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	// Creating Vertex-Array-Object (VAO). Not used here, check the handout to see its importance.
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	///////////////////////////////////////////////////////////////////////////////////////////
	/// Start Drawing your primitive
	////////////////////////////////

	// Set the background color to white
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	// 1) create the data array (stored in RAM)
	GLfloat verts[] = {

		-1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	    -0.30f, -0.5f, 0.0f,

		0.30f, -0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,
		-0.30f, -0.5f, 0.0f,


	};

	// 2) create a buffer object name(ID) holder. (it is defined in Renderer.h)
	// vertexBufferID
	GLuint myBufferID;

	// 3) reserve/generate a buffer object name(ID).
	glGenBuffers(1, &myBufferID);
    // void glGenBuffers(GLsizei n, GLuint * buffers);
    // n: number of names to be generated. (you can generate more than one name)
    // buffers: names generated.
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);

	// 4) set vertexbufferID as the current GL_ARRAY_BUFFER.
    // note that since this is the first time we bind myBufferID,
    // in this step OpenGL will both allocate and bind the buffer object.
    // void glBindBuffer(GLenum target,GLuint buffer);
    // target: Specifies the target to which the buffer object is bound.
    // buffer: Specifies the name of a buffer object.

	// 5) allocate the mem in the GPU and copy the data from the RAM to the GPU,
    // in the current GL_ARRAY_BUFFER, which in our case is
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
    // void glBufferData(GLenum target,GLsizeiptr size,
    // const GLvoid * data,GLenum usage);
    // target:	Specifies the target buffer object.
    // size:	Specifies the size in bytes of the buffer object's new data store.
    // data:	Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.
    // usage:	Specifies the expected usage pattern of the data store.
    //	Usage can make performance difference, because it affects the place where the data is allocated,
    //	but since we won't change the data so we can make it GL_STATIC_DRAW.


	// Create and compile our GLSL program from the shaders
	 programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	// Use our shader
	glUseProgram(programID);
}

void Renderer::Draw()
{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
		
		glUseProgram(programID);

		//6) enable the desired attributes. (Please go to this section for more information about vertex attributes:
		// the attributes are 0 indexed, and here we have only one attribute.
		// void glEnableVertexAttribArray( GLuint index);
		// 1st attribute buffer : vertex position, later we'll add vertex color and other attributes
		glEnableVertexAttribArray(0);

		//7) specify the vertex-data format.
		//	void glVertexAttribPointer(
		//	GLuint index,	(the index of the attribute you are describing)
		//	GLint size,	(the number of elements in that attribute)
		// GLenum type,	(the type of each element in that attribute)
		// GLboolean normalized, (do you want to normalize the data?)
		// GLsizei stride,	(the offset between each instance of that attribute)
		// const GLvoid * pointer (the offset of the first component of the first instance of the attribute) );
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);


		// Draw the triangle !
		// note that glDrawArrays, uses the currently bound BO in GL_ARRAY_BUFFER.
		glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Binding will be written in the Draw function instead of the Initialize function if we want to draw more than one object
}

void Renderer::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}