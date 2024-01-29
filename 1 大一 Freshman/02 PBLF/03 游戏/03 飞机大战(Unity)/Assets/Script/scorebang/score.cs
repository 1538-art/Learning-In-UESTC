using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using UnityEngine.TextCore.Text;
using System.IO;

public class score : MonoBehaviour
{
    public ScrollRect ScrollRect;
    public string currentPlayerName; // 当前玩家的名称

    public List<PlayerScore> scoreList = new List<PlayerScore>();
    private string filePath;

    [System.Serializable]
    public class PlayerScore
    {
        public string PlayerName;
        public int score;
    }


    private void Awake()
    {
        currentPlayerName = PlayerPrefs.GetString("PlayerName", "visitor");
        Debug.Log(currentPlayerName);


        //filePath = Application.dataPath + "/scores.json";
        filePath = Application.persistentDataPath + "/feiji_scores.csv";

        //filePath = Path.Combine(Application.streamingAssetsPath, "scores.json");
        LoadScoreData();
        //Debug.Log("1");
        if (PlayerPrefs.GetInt("switch",0)==1)//从play场景跳转1
        {
            UpdateScore(currentPlayerName,PlayerPrefs.GetInt("score",0));//update目前有点重复，和add撞了
            //Debug.Log("1-1");

            PlayerPrefs.SetInt("switch", 0);//让他默认从start跳转
        }
        else//从开头跳转0
        {
            LoadScoreData();
            //Debug.Log("1-2");
        }
    }

    //添加新成绩到排行榜
    public void AddScore(string playerName, int score)
    {
        PlayerScore existingScore = scoreList.Find(p => p.PlayerName == playerName);

        if (existingScore != null)
        {
            //取同一玩家最高分
            if (score > existingScore.score)
            {
                existingScore.score = score;
                Debug.Log("Updated score for player " + playerName + ". New score: " + existingScore.score);
            }
            else
            {
                Debug.Log("Score not updated for player " + playerName + ". Existing score is higher.");
            }
        }
        else
        {
            //没该玩家，直接添加
            PlayerScore newScore = new PlayerScore();
            newScore.PlayerName = playerName;
            newScore.score = score;
            scoreList.Add(newScore);
            Debug.Log("Added new score for player " + playerName + ": " + score);
        }

        SortScores();
        SaveScoreData();
    }



    //删除玩家数据
    public void DeleteScore(string playerName)
    {
        PlayerScore scoreToRemove = scoreList.Find(p => p.PlayerName == playerName);
        if (scoreToRemove != null)
        {
            scoreList.Remove(scoreToRemove);
            SaveScoreData();
        }
    }

    // 更新特定玩家的成绩
    public void UpdateScore(string playerName, int newScore)
    {
        PlayerScore scoreToUpdate = scoreList.Find(p => p.PlayerName == playerName);
        if (scoreToUpdate != null)
        {
            scoreToUpdate.score = newScore;
            SortScores();
            SaveScoreData();
        }
        else
        {
            AddScore(playerName, newScore);
        }
    }

    //分数由低到高排序，同意分数同一微辞
    private void SortScores()
    {
        scoreList.Sort((x, y) =>
        {
            int scoreComparison = y.score.CompareTo(x.score);
            if (scoreComparison != 0)
            {
                return scoreComparison;
            }
            else
            {
                //分同，同位，名字排序
                return x.PlayerName.CompareTo(y.PlayerName);
            }
        });
    }

    //加载排行榜数据
    private void LoadScoreData()
    {
        if (File.Exists(filePath))
        {
            // 从CSV文件读取数据
            string[] lines = File.ReadAllLines(filePath);
            scoreList.Clear(); // 清空原有数据

            foreach (string line in lines)
            {
                string[] values = line.Split(','); // 使用逗号分隔值

                PlayerScore playerScore = new PlayerScore();
                playerScore.PlayerName = values[0];
                playerScore.score = int.Parse(values[1]);

                scoreList.Add(playerScore);
            }

            DisplayLeaderboard();
            Debug.Log("Loaded score data from CSV.");
        }
        else
        {
            Debug.LogWarning("No score data found. Creating a new example.");

            // 创建一个新的排行榜数据示例
            PlayerScore exampleScore = new PlayerScore();
            exampleScore.PlayerName = "visitor";
            exampleScore.score = 0;

            scoreList.Add(exampleScore);

            SaveScoreData();
        }
    }

    private void SaveScoreData()
    {
        // 将数据保存为CSV格式
        List<string> lines = new List<string>();

        foreach (PlayerScore score in scoreList)
        {
            string line = $"{score.PlayerName},{score.score}";
            lines.Add(line);
        }

        File.WriteAllLines(filePath, lines);
        DisplayLeaderboard();
        Debug.Log("Saved score data to CSV.");
    }

    public Text teshu;

    //展示排行榜
    private void DisplayLeaderboard()
    {
        SortScores(); //排序

        string leaderboardInfo = "";
        int rank = 1; //初始化rank

        for (int i = 0; i < scoreList.Count; i++)
        {
            string playerName = scoreList[i].PlayerName;
            string playerScore = scoreList[i].score.ToString();

            currentPlayerName = PlayerPrefs.GetString("PlayerName", "visitor");

            if (playerName == currentPlayerName)
            {
                playerName = "<color=yellow>" + playerName + "</color>"; //标黄当前玩家（add的或者开局输入的playerprefs存储）
                teshu.text = $"[{rank}] {playerName}: {playerScore}\n";
            }

            leaderboardInfo += $"[{rank}] {playerName}: {playerScore}\n";

            //如果当前分数与上一个分数相同，则排名保持不变
            if (i < scoreList.Count - 1 && scoreList[i].score != scoreList[i + 1].score)
            {
                rank++; //分数不同，排名递增
            }
        }

        Text leaderboardText = ScrollRect.content.GetComponent<Text>();
        leaderboardText.text = leaderboardInfo; //更新content
    }

    //补充的添加、删除和更新分数的功能//先放着暂时用不上
    //添加新成绩
    public void AddPlayerScore(string playerName, int score)
    {
        AddScore(playerName, score);
    }

    // 删除特定玩家的成绩
    public void RemovePlayerScore(string playerName)
    {
        DeleteScore(playerName);
    }

    // 更新特定玩家的成绩
    public void UpdatePlayerScore(string playerName, int newScore)
    {
        UpdateScore(playerName, newScore);
    }


    //从input输入框记录成绩
    public InputField nameInputField;
    public InputField scoreInputField;
    public void Addscre()
    {
        PlayerPrefs.SetString("PlayerName", nameInputField.text);
        int score = ConvertToInt(scoreInputField.text);
        AddScore(nameInputField.text, score);
    }

    public GameObject bannar;

    public int ConvertToInt(string textValue)
    {
        int convertedNumber;

        if (int.TryParse(textValue, out convertedNumber))
        {
            Debug.Log("Converted number: " + convertedNumber);
            return convertedNumber;
        }
        else
        {
            Debug.Log("Failed to convert text to integer!");
            bannar.SetActive(true);
            bannar.transform.GetChild(0).GetComponent<Text>().text = "请输入数字!";
            return 0;
        }
    }



    public void Guanbi()
    {
        bannar.SetActive(false);
    }

    //对于查找玩家数据面板的操控
    public GameObject Findscore;
    public void FindOpen()
    {
        Findscore.SetActive(true);
        findname.text = "";
        findtext.text = "";
    }

    public void FindClose()
    {
        Findscore.SetActive(false);
    }

    public InputField findname;
    public Text findtext;
    public void Findbyname()
    {
        if(findname.text!="")
        {
            string playerName = findname.text;
            PlayerScore existingScore = scoreList.Find(p => p.PlayerName == playerName);
            if(existingScore!=null)
            {
                int score = existingScore.score;
                // 使用 Sort() 函数重新排序以获取玩家的排名
                List<PlayerScore> sortedList = new List<PlayerScore>(scoreList);
                sortedList.Sort((x, y) => y.score.CompareTo(x.score));

                int rank = sortedList.FindIndex(p => p.PlayerName == playerName) + 1;
                //Debug.Log("玩家" + playerName + "的分数为" + score);
                findtext.text = "玩家：" + playerName + "\n分数: " + score+"\n排名："+rank;
            }
            else
            {
                findtext.text = "请输入已存在的玩家昵称";
            }

        }
        else
        {
            findtext.text = "请输入要查询的玩家昵称";
        }
    }

    public GameObject deletebannar;

    public void DeleteClose()
    {
        deletebannar.SetActive(false);
    }
    public InputField deletename;
    public Text deletetext;
    public void DeleteOpen()
    {
        deletebannar.SetActive(true);
        deletename.text = "";
        deletetext.text = "";
    }

    public void Deletebyname()
    {
        if (deletename.text != "")
        {
            string playerName = deletename.text;
            PlayerScore existingScore = scoreList.Find(p => p.PlayerName == playerName);
            if (existingScore != null)
            {
                int score = existingScore.score;
                DeleteScore(playerName);
                deletetext.text = "分数为" + score + "的玩家:" + playerName + "已删除";
            }
            else
            {
                deletetext.text = "该玩家不存在，无法删除";
            }

        }
        else
        {
            deletetext.text = "请输入要删除的玩家昵称";
        }
    }
}
