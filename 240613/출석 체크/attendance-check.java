import java.util.*;
/*
- 수업 시작시간 전에 활동 기록 있을 것
- 수업 종료 후 
*/
public class Main {
    public static void main(String[] args) {
        // 여기에 코드를 작성해주세요.
        Scanner sc = new Scanner(System.in);

        String s = sc.next();
        String e = sc.next();
        String q = sc.next();
        int n = sc.nextInt();

        // System.out.println(s + " " + e + " " + q);
        
        Map<String, ArrayList<String>> students = new TreeMap<>();
        for(int i = 0; i < n; i++){
            String time = sc.next();
            String name = sc.next();
                
            ArrayList<String> tmp = new ArrayList<>();
            if(students.containsKey(time)){
                tmp = students.get(time);
                tmp.add(name);

                students.put(time, tmp);
            }
            else{
                tmp.add(name);
                students.put(time, tmp);
            }
        }

        int[] start = Arrays.stream(s.split(":")).mapToInt(Integer:: parseInt).toArray();
        int[] end = Arrays.stream(e.split(":")).mapToInt(Integer:: parseInt).toArray();
        int[] pass = Arrays.stream(q.split(":")).mapToInt(Integer:: parseInt).toArray();

        int answer = 0;

        Set<String> first = new HashSet<>();
        Set<String> second = new HashSet<>();

        // 08:00 11:22 18:33
        for (String key : students.keySet()) {
            int[] current = Arrays.stream(key.split(":")).mapToInt(Integer:: parseInt).toArray();

            // 9:00 이후 11:00 이전 제외 
            if(start[0] < current[0] && current[0] < end[0]) { continue; }
            // 19:00 이후 제외
            if(pass[0] < current[0]) { continue; }
            
            // System.out.println(key + " " + students.get(key));

            // 8:10
            if((current[0] == start[0] && current[1] <= start[1])
            // 6:23
            || (current[0] < start[0])){
                first.addAll(students.get(key));
            }

            // 11:23
            if((end[0] == current[0] && end[1] <= current[1])
            // 18:30
            || (current[0] == pass[0] && current[1] <= pass[1])
            // 13:00
            || (end[0] < current[0] && current[0] < pass[0])){
                second.addAll(students.get(key));
            }
        }        

        // System.out.println(first);
        // System.out.println(second);
        first.retainAll(second);

        // System.out.println(first);
        System.out.println(first.size());
        
        
    }
}