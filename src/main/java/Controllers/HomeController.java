@Controller
public class HomeController {

    @RequestMapping("/")
    public String home(){
        return "index";
    }

}