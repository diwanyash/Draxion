#version 330 core

out vec4 FragOut;
in vec4 VC;

void main()
{
	FragOut = vec4( 1.0 ,1.0, (VC.x+VC.y) ,1.0 );
}