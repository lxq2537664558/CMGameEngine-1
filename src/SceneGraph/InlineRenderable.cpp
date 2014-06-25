#include<hgl/graph/VertexBuffer.h>
#include<hgl/graph/Renderable.h>
#include<hgl/graph/Material.h>
#include<hgl/graph/Render.h>
#include<hgl/graph/Shader.h>
#include<hgl/graph/TextureFormat.h>
#include<hgl/type/Color4f.h>

namespace hgl
{
	namespace graph
	{
		Texture2D *BlackWhiteGrid		=nullptr;

		Renderable *SolidCube	=nullptr;
		Renderable *WireCube	=nullptr;

		Renderable *SolidRect	=nullptr;
		Renderable *WireRect	=nullptr;
		Renderable *TextureRect	=nullptr;

		Renderable *SolidCircle	=nullptr;
		Renderable *WireCircle	=nullptr;
	}//namespace graph

	namespace graph
	{
		///**
		//* 创建一个点的可渲染数据
		//* @param vertex 顶点坐标
		//* @param color 颜色
		//* @param size 点尺寸
		//* return 可渲染数据
		//*/
		//Renderable *CreateRenderablePoint(const Vector3f &vertex,const Color4f &color,double size)
		//{
		//	Renderable *obj=CreateRenderable();
		//	Material *mtl=CreateMaterial();

		//	//设置材质
		//	mtl->SetColor(color);					//设置颜色

		//	obj->SetMaterial(mtl);					//设置材质

		//	//设置图元类型
		//	obj->SetPrimitive(HGL_POINTS);			//设置为画点
		//	//obj->SetPointSize(size);				//设置点尺寸

		//	//创建顶点缓冲区
		//	VB3f *vertex=new VB3f(1);				//创建一个3D坐标点、浮点数据的缓冲区

		//	vertex->Begin();
		//		//vertex->Write(vertex.x,vertex.y,vertex.z);
		//		vertex->Write(vertex);
		//	vertex->End();

		//	obj->SetVertexBuffer(vbtVertex,vertex);

		//	return(obj);
		//}

		/**
		* 创建一条线的可渲染数据
		* @param start 线条起始点
		* @param end 线条终点
		* @param color 线条颜色
		*/
		Renderable *CreateRenderableLine(const Vector3f &start,const Vector3f &end,const Color4f &color)
		{
			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			//设置材质
			mtl->SetColorMaterial(true);			//设置使用颜色追踪(默认其实就是)
			mtl->SetColor(color);					//设置颜色
			obj->SetMaterial(mtl,true);				//设置材质

			//设置图元类型
			obj->SetPrimitive(HGL_PRIM_LINES);		//设置为画线
			//obj->SetPointSize(size);				//设置点尺寸

			//创建顶点缓冲区
			VB3f *vertex=new VB3f(2);				//创建一个3D坐标点、浮点数据的缓冲区

			vertex->Begin();
				vertex->Write(start);
				vertex->Write(end);
			vertex->End();

			obj->SetVertex(vertex);

			return(obj);
		}

		/**
		/* 创建一个画坐标轴的可渲染数据(尺寸为1)
		/* @return 可渲染数据
		/*/
		Renderable *CreateRenderableAxis()
		{
			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			//设置材质
			mtl->SetColorMaterial(false);			//不使用材质中的颜色
			obj->SetMaterial(mtl,true);				//设置材质

			//设置图元类型
			obj->SetPrimitive(HGL_PRIM_LINES);		//设置为画线

			//创建顶点缓冲区
			VB3f *vertex=new VB3f(6);				//创建一个3D坐标点、浮点数据的缓冲区
			VB3f *color=new VB3f(6);				//创建一个4元颜色、浮点数据的缓冲区

			color->Begin();
			vertex->Begin();
				color->Write(1,0,0);vertex->Write(0,0,0);color->Write(1,0,0);vertex->Write(1,0,0);
				color->Write(0,1,0);vertex->Write(0,0,0);color->Write(0,1,0);vertex->Write(0,1,0);
				color->Write(0,0,1);vertex->Write(0,0,0);color->Write(0,0,1);vertex->Write(0,0,1);
			vertex->End();
			color->End();

			obj->SetVertex(vertex);
			obj->SetColor(color,HGL_COLOR_RGB);

			return(obj);
		}

		/**
		* 画一个平面网格
		* @param v0 网格顶点0
		* @param v1 网格顶点1
		* @param v2 网格顶点2
		* @param v3 网格顶点3
		* @param step01 顶点0至1之间的格数
		* @param step12 顶点2至3之间的格数
		* @param color 颜色
		* @return 可渲染数据
		*/
		Renderable *CreateRenderablePlaneGrid(	const Vector3f &v0,														///<创建一个平面网格的可渲染数据
												const Vector3f &v1,
												const Vector3f &v2,
												const Vector3f &v3,
												int step01,
												int step12,
												const Color4f &color)
		{
			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			//设置材质
			mtl->SetColorMaterial(true);			//使用颜色追踪材质
			mtl->SetColor(color);					//设置颜色

			obj->SetMaterial(mtl,true);				//设置材质

			//设置图元类型
			obj->SetPrimitive(HGL_PRIM_LINES);		//设置为画线

			//创建顶点缓冲区
			VB3f *vertex=new VB3f(((step01+1)+(step12+1))*2);				//创建一个3D坐标点、浮点数据的缓冲区

			vertex->Begin();
				for(int row=0;row<=step01;row++)
				{
					float pos=float(row)/float(step01);

					Vector3f start	=to(v0,v1,pos);
					Vector3f end	=to(v3,v2,pos);

					vertex->WriteLine(start,end);
				}

				for(int col=0;col<=step12;col++)
				{
					float pos=float(col)/float(step12);

					Vector3f start	=to(v1,v2,pos);
					Vector3f end	=to(v0,v3,pos);

					vertex->WriteLine(start,end);
				}
			vertex->End();

			obj->SetVertex(vertex);

			return(obj);
		}

		/**
		* 创建一个立方体的可渲染数据
		* @return 可渲染数据
		*/
		Renderable *CreateRenderableCube()
		{								// Points of a cube.
			/*     4            5 */	const float points[]={	-0.5f, -0.5f, -0.5f,	-0.5f, -0.5f, +0.5f,	+0.5f, -0.5f, +0.5f,	+0.5f, -0.5f, -0.5f,	-0.5f, +0.5f, -0.5f,	-0.5f, +0.5f, +0.5f,
			/* 	   *------------* */							+0.5f, +0.5f, +0.5f,	+0.5f, +0.5f, -0.5f,	-0.5f, -0.5f, -0.5f,	-0.5f, +0.5f, -0.5f,	+0.5f, +0.5f, -0.5f,	+0.5f, -0.5f, -0.5f,
			/*    /|           /| */							-0.5f, -0.5f, +0.5f,	-0.5f, +0.5f, +0.5f,	+0.5f, +0.5f, +0.5f,	+0.5f, -0.5f, +0.5f,	-0.5f, -0.5f, -0.5f,	-0.5f, -0.5f, +0.5f,
			/*  0/ |         1/ | */							-0.5f, +0.5f, +0.5f,	-0.5f, +0.5f, -0.5f,	+0.5f, -0.5f, -0.5f,	+0.5f, -0.5f, +0.5f,	+0.5f, +0.5f, +0.5f,	+0.5f, +0.5f, -0.5f	};
			/*  *--+---------*  | */	// Normals of a cube.
			/*  |  |         |  | */	const float normals[]={ +0.0f, -1.0f, +0.0f,	+0.0f, -1.0f, +0.0f,	+0.0f, -1.0f, +0.0f,	+0.0f, -1.0f, +0.0f,	+0.0f, +1.0f, +0.0f,	+0.0f, +1.0f, +0.0f,
			/*  | 7|         | 6| */							+0.0f, +1.0f, +0.0f,	+0.0f, +1.0f, +0.0f,	+0.0f, +0.0f, -1.0f,	+0.0f, +0.0f, -1.0f,	+0.0f, +0.0f, -1.0f,	+0.0f, +0.0f, -1.0f,
			/*  |  *---------+--* */							+0.0f, +0.0f, +1.0f,	+0.0f, +0.0f, +1.0f,	+0.0f, +0.0f, +1.0f,	+0.0f, +0.0f, +1.0f,	-1.0f, +0.0f, +0.0f,	-1.0f, +0.0f, +0.0f,
			/*  | /          | /  */							-1.0f, +0.0f, +0.0f,	-1.0f, +0.0f, +0.0f,	+1.0f, +0.0f, +0.0f,	+1.0f, +0.0f, +0.0f,	+1.0f, +0.0f, +0.0f,	+1.0f, +0.0f, +0.0f	};
			/*  |/          2|/	  */	// The associated indices.
			/* 3*------------*	  */	const uint indices[]={	0,	2,	1,	0,	3,	2,	4,	5,	6,	4,	6,	7,	8,	9,	10,	8,	10,	11, 12,	15,	14,	12,	14,	13, 16,	17,	18,	16,	18,	19, 20,	23,	22,	20,	22,	21	};

			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			obj->SetMaterial(mtl,true);				//设置材质

			//设置图元类型
			obj->SetPrimitive(HGL_PRIM_TRIANGLES);	//设置为画三角形

			obj->SetVertex(new VB3f(24,points));
			obj->SetNormal(new VB3f(24,normals));
			obj->SetIndex(new VB1ui(6*2*3,indices));

			return(obj);
		}

		/**
		* 创建一个线框立方体的可渲染数据
		* @return 可渲染数据
		*/
		Renderable *CreateRenderableWireCube()
		{								// Points of a cube.
			/*     4            5 */	const float points[]={	-0.5f, +0.5f, -0.5f,	//	0
			/* 	   *------------* */							+0.5f, +0.5f, -0.5f,	//	1
			/*    /|           /| */							+0.5f, -0.5f, -0.5f,	//	2
			/*  0/ |         1/ | */							-0.5f, -0.5f, -0.5f,	//	3
			/*  *--+---------*  | */							-0.5f, +0.5f, +0.5f,	//	4
			/*  |  |         |  | */							+0.5f, +0.5f, +0.5f,	//	5
			/*  | 7|         | 6| */							+0.5f, -0.5f, +0.5f,	//	6
			/*  |  *---------+--* */							-0.5f, -0.5f, +0.5f};	//	7
			/*  | /          | /  */
			/*  |/          2|/	  */	// The associated indices.
			/* 3*------------*	  */	const uint indices[]={	0,1,1,2,2,3,3,0,	0,4,1,5,2,6,3,7,	4,5,5,6,6,7,7,4};

			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			obj->SetMaterial(mtl,true);				//设置材质

			//设置图元类型
			obj->SetPrimitive(HGL_PRIM_LINES);		//设置为画三角形

			obj->SetVertex(new VB3f(8,points));
			obj->SetIndex(new VB1ui(12*2,indices));

			obj->AutoCreateShader(true);

			return(obj);
		}

		const float RectVertex[8]={0,0, 1,0, 1,1, 0,1};

		Renderable *CreateRenderableRect(uint prim)
		{
			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();

			obj->SetMaterial(mtl,true);

			obj->SetPrimitive(prim);

			obj->SetVertex(new VB2f(4,RectVertex));

			obj->AutoCreateShader(true);

			return(obj);
		}

		/**
		* 创建一个2D矩形的可渲染数据
		*/
		Renderable *CreateRenderableRect()
		{
			return CreateRenderableRect(HGL_PRIM_TRIANGLE_FAN);
		}

		/**
		* 创建一个2D线框矩形的可渲染数据
		*/
		Renderable *CreateRenderableWireRect()
		{
			return CreateRenderableRect(HGL_PRIM_LINE_LOOP);
		}

		Renderable *CreateRenderableTextureRect()
		{
			Renderable *obj=CreateRenderableRect(HGL_PRIM_TRIANGLE_FAN);
			Material *mtl=obj->GetMaterial();

			obj->SetTexCoord(mtcDiffuse,vbtDiffuseTexCoord,new VB2f(4,RectVertex));
			mtl->SetTexture(mtcDiffuse,BlackWhiteGrid);

			obj->AutoCreateShader(true);

			mtl->ClearTexture(mtcDiffuse);

			return(obj);
		}

		/**
		* 创建一个2D空心圆,圆心为0,0,半径为1
		* @param edge 边数
		*/
		Renderable *CreateRenderableWireCircle(int edge)
		{
			const Vector4f start(1,0,0,1);
			const Vector3f axis(0,0,1);

			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();
			VB2f *vertex=new VB2f(edge);

			obj->SetMaterial(mtl,true);

			obj->SetPrimitive(HGL_PRIM_LINE_LOOP);

			vertex->Begin();

			for(int i=0;i<edge;i++)
			{
				const Vector4f pos=start*rotate(float(i)/float(edge)*360.0,axis);

				vertex->Write(pos.data());
			}

			vertex->End();

			obj->SetVertex(vertex);

			obj->AutoCreateShader(true);

			return(obj);
		}

		/**
		* 创建一个2D实心圆,圆心为0,0,半径为1
		* @param edge 边数
		*/
		Renderable *CreateRenderableCircle(int edge)
		{
			const Vector4f start(1,0,0,1);
			const Vector3f axis(0,0,1);

			Renderable *obj=CreateRenderable();
			Material *mtl=CreateMaterial();
			VB2f *vertex=new VB2f(edge+2);

			obj->SetMaterial(mtl,true);

			obj->SetPrimitive(HGL_PRIM_TRIANGLE_FAN);

			vertex->Begin();

			vertex->Write(0,0);

			for(int i=0;i<=edge;i++)
			{
				const Vector4f pos=start*rotate(float(i)/float(edge)*360.0,axis);

				vertex->Write(pos.data());
			}

			vertex->End();

			obj->SetVertex(vertex);

			obj->AutoCreateShader(true);

			return(obj);
		}
	}//namespace graph

	namespace graph
	{
		void CreateBlackWhiteGridTexture()
		{
			const uint8 black_white_grid[4]={0xFF,0x00,0x00,0xFF};

			BlackWhiteGrid=CreateTexture2D();
			BlackWhiteGrid->SetImage(2,2,(void *)black_white_grid,4,HGL_SF_R8,HGL_R8);
		}

		void InitInlineRenderable()
		{
			CreateBlackWhiteGridTexture();

			SolidCube=CreateRenderableCube();
			WireCube=CreateRenderableWireCube();

			SolidRect=CreateRenderableRect();
			WireRect=CreateRenderableWireRect();
			TextureRect=CreateRenderableTextureRect();

			SolidCircle=CreateRenderableCircle(128);
			WireCircle=CreateRenderableWireCircle(128);
		}

		void ClearInlineRenderable()
		{
			SAFE_CLEAR(WireCircle);
			SAFE_CLEAR(SolidCircle);

			SAFE_CLEAR(WireRect);
			SAFE_CLEAR(SolidRect);
			SAFE_CLEAR(TextureRect);

			SAFE_CLEAR(WireCube);
			SAFE_CLEAR(SolidCube);

			SAFE_CLEAR(BlackWhiteGrid);
		}
	}//namespace graph
}//namespace hgl
