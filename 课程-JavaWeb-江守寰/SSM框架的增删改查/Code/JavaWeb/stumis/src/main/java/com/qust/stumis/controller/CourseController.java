package com.qust.stumis.controller;

import com.qust.stumis.entity.Course;
import com.qust.stumis.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.stereotype.Repository;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
public class CourseController {
    @Autowired
    CourseService courseService;

    @RequestMapping("search")
    public ModelAndView search(){
        List<Course> list = courseService.search();

//        for(Course course : list){
//            System.out.println(course.getId()+' '+course.getCno()+' '+course.getCname()+' '+course.getCredit()+' '
//                    +course.getCredit()+' '+course.getCredit()+' '+course.getMemo());
//        }

        ModelAndView mv = new ModelAndView("course");
        mv.addObject("courses", list);
        return mv;

    }

    @RequestMapping("showAdd")
    public String showAdd(){
        return "add";
    }

    @RequestMapping("add")
    public String add(Course course){
        boolean flag = courseService.add(course);
        if(flag){
            return "redirect:search";
        }
        return null;
    }

    @RequestMapping("delete")
    public String delete(String sno){
        boolean flag = courseService.delete(sno);
        if(flag){
            return "redirect:search";
        }
        return null;
    }

    @RequestMapping("modify")
    public ModelAndView modify(String cno){
        Course course = courseService.findByCno(cno);
        ModelAndView mv = new ModelAndView("update");
        mv.addObject("course", course);
        return mv;
    }

    @RequestMapping("save")
    public String save(Course course){
        boolean flag = courseService.add(course);
        if(flag){
            return "redirect:search";
        }
        return null;
    }
}
