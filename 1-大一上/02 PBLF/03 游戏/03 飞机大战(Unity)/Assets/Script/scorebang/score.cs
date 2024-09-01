using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using UnityEngine.TextCore.Text;
using System.IO;

public class score : MonoBehaviour
{
    public ScrollRect ScrollRect;
    public string currentPlayerName; // ��ǰ��ҵ�����

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
        if (PlayerPrefs.GetInt("switch",0)==1)//��play������ת1
        {
            UpdateScore(currentPlayerName,PlayerPrefs.GetInt("score",0));//updateĿǰ�е��ظ�����addײ��
            //Debug.Log("1-1");

            PlayerPrefs.SetInt("switch", 0);//����Ĭ�ϴ�start��ת
        }
        else//�ӿ�ͷ��ת0
        {
            LoadScoreData();
            //Debug.Log("1-2");
        }
    }

    //����³ɼ������а�
    public void AddScore(string playerName, int score)
    {
        PlayerScore existingScore = scoreList.Find(p => p.PlayerName == playerName);

        if (existingScore != null)
        {
            //ȡͬһ�����߷�
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
            //û����ң�ֱ�����
            PlayerScore newScore = new PlayerScore();
            newScore.PlayerName = playerName;
            newScore.score = score;
            scoreList.Add(newScore);
            Debug.Log("Added new score for player " + playerName + ": " + score);
        }

        SortScores();
        SaveScoreData();
    }



    //ɾ���������
    public void DeleteScore(string playerName)
    {
        PlayerScore scoreToRemove = scoreList.Find(p => p.PlayerName == playerName);
        if (scoreToRemove != null)
        {
            scoreList.Remove(scoreToRemove);
            SaveScoreData();
        }
    }

    // �����ض���ҵĳɼ�
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

    //�����ɵ͵�������ͬ�����ͬһ΢��
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
                //��ͬ��ͬλ����������
                return x.PlayerName.CompareTo(y.PlayerName);
            }
        });
    }

    //�������а�����
    private void LoadScoreData()
    {
        if (File.Exists(filePath))
        {
            // ��CSV�ļ���ȡ����
            string[] lines = File.ReadAllLines(filePath);
            scoreList.Clear(); // ���ԭ������

            foreach (string line in lines)
            {
                string[] values = line.Split(','); // ʹ�ö��ŷָ�ֵ

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

            // ����һ���µ����а�����ʾ��
            PlayerScore exampleScore = new PlayerScore();
            exampleScore.PlayerName = "visitor";
            exampleScore.score = 0;

            scoreList.Add(exampleScore);

            SaveScoreData();
        }
    }

    private void SaveScoreData()
    {
        // �����ݱ���ΪCSV��ʽ
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

    //չʾ���а�
    private void DisplayLeaderboard()
    {
        SortScores(); //����

        string leaderboardInfo = "";
        int rank = 1; //��ʼ��rank

        for (int i = 0; i < scoreList.Count; i++)
        {
            string playerName = scoreList[i].PlayerName;
            string playerScore = scoreList[i].score.ToString();

            currentPlayerName = PlayerPrefs.GetString("PlayerName", "visitor");

            if (playerName == currentPlayerName)
            {
                playerName = "<color=yellow>" + playerName + "</color>"; //��Ƶ�ǰ��ң�add�Ļ��߿��������playerprefs�洢��
                teshu.text = $"[{rank}] {playerName}: {playerScore}\n";
            }

            leaderboardInfo += $"[{rank}] {playerName}: {playerScore}\n";

            //�����ǰ��������һ��������ͬ�����������ֲ���
            if (i < scoreList.Count - 1 && scoreList[i].score != scoreList[i + 1].score)
            {
                rank++; //������ͬ����������
            }
        }

        Text leaderboardText = ScrollRect.content.GetComponent<Text>();
        leaderboardText.text = leaderboardInfo; //����content
    }

    //�������ӡ�ɾ���͸��·����Ĺ���//�ȷ�����ʱ�ò���
    //����³ɼ�
    public void AddPlayerScore(string playerName, int score)
    {
        AddScore(playerName, score);
    }

    // ɾ���ض���ҵĳɼ�
    public void RemovePlayerScore(string playerName)
    {
        DeleteScore(playerName);
    }

    // �����ض���ҵĳɼ�
    public void UpdatePlayerScore(string playerName, int newScore)
    {
        UpdateScore(playerName, newScore);
    }


    //��input������¼�ɼ�
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
            bannar.transform.GetChild(0).GetComponent<Text>().text = "����������!";
            return 0;
        }
    }



    public void Guanbi()
    {
        bannar.SetActive(false);
    }

    //���ڲ�������������Ĳٿ�
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
                // ʹ�� Sort() �������������Ի�ȡ��ҵ�����
                List<PlayerScore> sortedList = new List<PlayerScore>(scoreList);
                sortedList.Sort((x, y) => y.score.CompareTo(x.score));

                int rank = sortedList.FindIndex(p => p.PlayerName == playerName) + 1;
                //Debug.Log("���" + playerName + "�ķ���Ϊ" + score);
                findtext.text = "��ң�" + playerName + "\n����: " + score+"\n������"+rank;
            }
            else
            {
                findtext.text = "�������Ѵ��ڵ�����ǳ�";
            }

        }
        else
        {
            findtext.text = "������Ҫ��ѯ������ǳ�";
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
                deletetext.text = "����Ϊ" + score + "�����:" + playerName + "��ɾ��";
            }
            else
            {
                deletetext.text = "����Ҳ����ڣ��޷�ɾ��";
            }

        }
        else
        {
            deletetext.text = "������Ҫɾ��������ǳ�";
        }
    }
}
