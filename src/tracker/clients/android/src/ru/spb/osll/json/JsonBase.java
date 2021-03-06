package ru.spb.osll.json;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicHeader;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.json.JSONException;
import org.json.JSONObject;

public class JsonBase {
    private final int TIMEOUT_MILLISEC = 20000; // = 10 seconds
    private HttpClient m_httpClient;
    private HttpPost m_httpPost;
    
    private static JsonBase instanceJSBase;
    public static JsonBase instance(){
    	if (instanceJSBase == null)
    		instanceJSBase = new JsonBase();
    	return instanceJSBase;
    }
    
	private JsonBase() {
		HttpParams httpParams = new BasicHttpParams();
		HttpConnectionParams.setConnectionTimeout(httpParams, TIMEOUT_MILLISEC);
	    HttpConnectionParams.setSoTimeout(httpParams, TIMEOUT_MILLISEC);

		m_httpClient = new DefaultHttpClient(httpParams);
		m_httpPost = new HttpPost();
	}

	public JSONObject doRequest(JSONObject jsonObject, URI uri) throws IOException, ClientProtocolException, JSONException{
		StringEntity stringEntity = new StringEntity(jsonObject.toString());
		stringEntity.setContentEncoding(new BasicHeader(HTTP.CONTENT_ENCODING, "application/json"));
		stringEntity.setContentType(new BasicHeader(HTTP.CONTENT_TYPE, "application/json"));
		m_httpPost.setEntity(stringEntity);
		m_httpPost.setURI(uri);
		
		HttpResponse httpResponse = m_httpClient.execute(m_httpPost);
		String resultStr = convertStreamToString(httpResponse.getEntity().getContent());
		JSONObject result = new JSONObject(resultStr);
		return result;
	}
	
	
    private String convertStreamToString(InputStream is) {
        /*
         * To convert the InputStream to String we use the BufferedReader.readLine()
         * method. We iterate until the BufferedReader return null which means
         * there's no more data to read. Each line will appended to a StringBuilder
         * and returned as String.
         */
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();
 
        String line = null;
        try {
            while ((line = reader.readLine()) != null) {
                sb.append(line + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return sb.toString();
    }
    
    public static String getString(JSONObject jsonObject, String key){
    	String result = null;
    	try {
			result = jsonObject.getString(key);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
    }    
}
