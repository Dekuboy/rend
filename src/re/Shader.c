#include "internal.h"

const char *vertSrc =
  "attribute vec4 a_Position;              " \
  "                                        " \
  "void main()                             " \
  "{                                       " \
  "  gl_Position = a_Position;             " \
  "}                                       " \
  "                                        ";

const char *fragSrc =
  "void main()                        " \
  "{                                  " \
  "  gl_FragColor = vec4(1, 0, 0, 1); " \
  "}                                  ";

ref(ReShader) _ReShaderCreate(ref(ReContext) context)
{
  ref(ReShader) rtn = NULL;
  GLuint vertId = 0;
  GLuint fragId = 0;
  int success = 0;
  int length = 0;
  vector(GLchar) infoLog = NULL;

  rtn = allocate(ReShader);
  _(rtn).id = glCreateProgram();
  _RePollForError();

  if(_(rtn).id == 0)
  {
    panic("Failed to create shader program");
  }

  vertId = glCreateShader(GL_VERTEX_SHADER);
  _RePollForError();

  glShaderSource(vertId, 1, &vertSrc, NULL);
  _RePollForError();

  glCompileShader(vertId);
  _RePollForError();

  glGetShaderiv(vertId, GL_COMPILE_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetShaderInfoLog(vertId, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  fragId = glCreateShader(GL_FRAGMENT_SHADER);
  _RePollForError();

  glShaderSource(fragId, 1, &fragSrc, NULL);
  _RePollForError();

  glCompileShader(fragId);
  _RePollForError();

  glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetShaderInfoLog(fragId, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  glAttachShader(_(rtn).id, vertId);
  _RePollForError();

  glAttachShader(_(rtn).id, fragId);
  _RePollForError();

  glBindAttribLocation(_(rtn).id, 0, "a_Position");
  _RePollForError();

  glLinkProgram(_(rtn).id);
  _RePollForError();

  glGetProgramiv(_(rtn).id, GL_LINK_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetProgramiv(_(rtn).id, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetProgramInfoLog(_(rtn).id, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  glDetachShader(_(rtn).id, vertId);
  _RePollForError();

  glDetachShader(_(rtn).id, fragId);
  _RePollForError();

  glDeleteShader(vertId);
  _RePollForError();

  glDeleteShader(fragId);
  _RePollForError();

  return rtn;
}

void _ReShaderDestroy(ref(ReShader) ctx)
{
  glDeleteProgram(_(ctx).id);
  release(ctx);
}

GLuint _ReShaderId(ref(ReShader) ctx)
{
  return _(ctx).id;
}
