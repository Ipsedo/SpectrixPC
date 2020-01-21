in vec3 a_vertex;

// Valeurs qui restent constantes pour le modèle entier.
uniform mat4 u_depth_mvp;

void main(){
 gl_Position =  u_depthMVP * vec4(vertexPosition_modelspace,1);
}
