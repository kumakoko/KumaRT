/*!
 * \file krt_world.h
 * \date 2020/03/17 21:45
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
*/

#ifndef krt_world_h__
#define krt_world_h__

#include "krt_tools_macro.h"
#include "krt_view_plane.h"
#include "krt_color_rgb.h"
#include "krt_camera.h"
#include "krt_geometry_object.h"
#include "krt_tracer.h"
#include "krt_light.h"
#include "krt_shade_helper.h"

namespace krt
{
    class World : public Object
    {
    public:
        /*********************************************************
        拿到本场景对应的默认背景颜色，用来作为显示窗口的缺省背景颜色
        @return 本场景对应的默认背景颜色        
        *********************************************************/
        KRT_INLINE RGBColor background_color() const
        {
            return background_color_;
        }

        /*********************************************************
        构造函数        
        *********************************************************/
        World();

        /*********************************************************
        构造函数
        @param  const char* name 该场景的名字     
        *********************************************************/
        World(const char* name);

        /*********************************************************
        构造函数
        @param  const std::string& name 该场景的名字         
        *********************************************************/
        World(const std::string& name);

        /*********************************************************
        析构函数       
        *********************************************************/
        ~World();

        /*********************************************************
        在删除本对象，执行析构函数之前，需要主动调用一下此函数，用来清理
        一下本对象所引用到的其他资源       
        *********************************************************/
        virtual void Cleanup();

        /*********************************************************
        给本场景添加几何对象
        @param  GeometricObjectSPtr object_ptr 几何对象      
        *********************************************************/
        KRT_INLINE void AddGeometryObject(GeometricObjectSPtr object_ptr)
        {
            objects_.push_back(object_ptr);
        }

        KRT_INLINE void AddLight(LightSPtr light_ptr)
        {
            lights_.push_back(light_ptr);
        }

        /*********************************************************
        
        @param  LightSPtr light_ptr
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        KRT_INLINE void set_ambient_light(LightSPtr light_ptr)
        {
            ambient_light_ = light_ptr;
        }

        /*********************************************************
        
        @param  CameraSPtr c_ptr
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        KRT_INLINE void set_camera(CameraSPtr c_ptr)
        {
            main_camera_ = c_ptr;
        }

        /*********************************************************
        
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        virtual void Build() = 0;

        /*********************************************************
        
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        void RenderScene();

        /*********************************************************
        
        @param  const RGBColor & c
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        RGBColor MaxToOne(const RGBColor& c) const;

        /*********************************************************
        
        @param  const RGBColor & c
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        RGBColor ClampToColor(const RGBColor& c) const;

        /*********************************************************
        
        @param  const int row
        @param  const int column
        @param  const RGBColor & pixel_color
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        void DisplayPixel(const int row, const int column, const RGBColor& pixel_color);

        /*********************************************************
        把屏幕坐标系(x,y)对应的像素点的颜色值写入到缓冲区种
        @param  int x
        @param  int y
        @param  int red
        @param  int green
        @param  int blue
        *********************************************************/
        virtual void WritePixelToBuffer(int x, int y, int red, int green, int blue);

        /*********************************************************
        
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        virtual void MakePixelBuffer();

        /*********************************************************
        
        @param  const char * img_file
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        virtual void SavePixelToImageFile(const char* img_file);

        /*********************************************************
        
        @param  const Ray & ray
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        ShadeHelper HitObjects(const Ray& ray);

        KRT_INLINE ViewPlane& view_plane()
        {
            return view_plane_;
        }

        KRT_INLINE const ViewPlane& view_plane() const
        {
            return view_plane_;
        }

        KRT_INLINE const Tracer* tracer() const
        {
            return tracer_;
        }

        KRT_INLINE Tracer* tracer()
        {
            return tracer_;
        }

    protected:
        void delete_objects();
        void delete_lights();
    protected:
        /** * @brief 视平面  */
        ViewPlane view_plane_;

        /** * @brief 缺省的背景色  */
        RGBColor background_color_;

        /** * @brief 光线追踪器  */
        Tracer* tracer_;

        /** * @brief 默认的环境光  */
        LightSPtr ambient_light_;

        /** * @brief 默认的主摄像机  */
        CameraSPtr main_camera_;
        
        /** * @brief 场景中的几何体对象  */
        std::vector<GeometricObjectSPtr> objects_;

        /** * @brief 场景中的光源  */
        std::vector<LightSPtr> lights_;
    };
}

#endif // krt_world_h__